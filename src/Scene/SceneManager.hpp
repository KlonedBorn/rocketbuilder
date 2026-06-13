#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "Scene.hpp"

// Forward declaration only — defined in Core/Application.hpp.
namespace Game::Core
{
    struct AppContext;
}

namespace Game::Scene
{
    class SceneManager
    {
    public:
        // ── Transition request ────────────────────────────────────────────────
        // Scenes do not call these directly. Application calls requestPush /
        // requestPop / requestReplace on SceneManager, then calls
        // flushTransition() after the update tick so transitions are always
        // deferred to a clean frame boundary.
        struct Transition
        {
            enum class Kind
            {
                Push,
                Pop,
                Replace
            };
            Kind kind;
            std::string sceneId; // unused for Pop
        };

        void requestPush(const std::string &id);
        void requestPop();
        void requestReplace(const std::string &id);

        // Execute the pending transition (if any). Call once per frame, after
        // onUpdate, so a scene's update logic is never interrupted mid-frame.
        void flushTransition(Core::AppContext &ctx);

        // ── Registration ──────────────────────────────────────────────────────
        // Register a concrete scene type against a string ID.
        // Instances are constructed lazily — only when a push is flushed.
        // T must derive from Scene.
        template <typename T>
        void registerScene(const std::string &id)
        {
            static_assert(std::is_base_of_v<Scene, T>,
                          "T must derive from Game::Scene::Scene");

            if (m_registry.count(id))
                throw std::runtime_error("SceneManager: already registered: " + id);

            m_registry[id] = []() -> std::unique_ptr<Scene>
            {
                return std::make_unique<T>();
            };
        }

        // ── Lifecycle forwarding ──────────────────────────────────────────────
        // Application calls these each frame; they delegate to the top scene.
        void onEvent(Core::AppContext &ctx, const std::optional<sf::Event> &event);
        void onUpdate(Core::AppContext &ctx, sf::Time dt);
        void onRender(Core::AppContext &ctx, sf::RenderWindow &window);

        // ── Queries ───────────────────────────────────────────────────────────
        [[nodiscard]] bool isEmpty() const { return m_stack.empty(); }
        [[nodiscard]] std::size_t size() const { return m_stack.size(); }

    private:
        using Factory = std::function<std::unique_ptr<Scene>()>;

        std::unordered_map<std::string, Factory> m_registry;
        std::stack<std::unique_ptr<Scene>> m_stack;
        std::optional<Transition> m_pendingTransition;

        // ── Internal stack operations (called only by flushTransition) ────────
        void push(const std::string &id, Core::AppContext &ctx);
        void pop(Core::AppContext &ctx);
        void replace(const std::string &id, Core::AppContext &ctx);

        [[nodiscard]] std::unique_ptr<Scene> construct(const std::string &id) const;
    };

} // namespace Game::Scene