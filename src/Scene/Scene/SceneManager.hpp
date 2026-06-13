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

/**
 * @brief Forward declaration of AppContext.
 */
namespace Game::Core
{
    struct AppContext;
}

namespace Game::Scene
{
    /**
     * @brief Manages a stack of scenes and handles transitions between them.
     */
    class SceneManager
    {
    public:
        /**
         * @brief Represents a transition between scenes.
         * 
         * Scenes do not call these directly. Application calls requestPush /
         * requestPop / requestReplace on SceneManager, then calls
         * flushTransition() after the update tick so transitions are always
         * deferred to a clean frame boundary.
         */
        struct Transition
        {
            enum class Kind
            {
                Push,
                Pop,
                Replace
            };
            Kind kind;
            std::string sceneId; /**< ID of the scene to transition to (unused for Pop). */
        };

        /**
         * @brief Requests a new scene to be pushed onto the stack.
         * @param id The ID of the scene to push.
         */
        void requestPush(const std::string &id);

        /**
         * @brief Requests the current scene to be popped from the stack.
         */
        void requestPop();

        /**
         * @brief Requests the current scene to be replaced with a new one.
         * @param id The ID of the scene to replace with.
         */
        void requestReplace(const std::string &id);

        /**
         * @brief Executes the pending transition (if any).
         * 
         * Should be called once per frame, after onUpdate, so a scene's 
         * update logic is never interrupted mid-frame.
         * @param ctx The application context.
         */
        void flushTransition(Core::AppContext &ctx);

        /**
         * @brief Registers a concrete scene type against a string ID.
         * 
         * Instances are constructed lazily — only when a push is flushed.
         * @tparam T Concrete scene type, must derive from Scene.
         * @param id The ID to register the scene under.
         */
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

        /**
         * @brief Forwards event handling to the top scene.
         * @param ctx The application context.
         * @param event The event to forward.
         */
        void onEvent(Core::AppContext &ctx, const std::optional<sf::Event> &event);

        /**
         * @brief Forwards update logic to the top scene.
         * @param ctx The application context.
         * @param dt The time elapsed since the last frame.
         */
        void onUpdate(Core::AppContext &ctx, sf::Time dt);

        /**
         * @brief Forwards rendering to the top scene.
         * @param ctx The application context.
         * @param window The render window.
         */
        void onRender(Core::AppContext &ctx, sf::RenderWindow &window);

        /**
         * @brief Checks if the scene stack is empty.
         * @return True if the stack is empty, false otherwise.
         */
        [[nodiscard]] bool isEmpty() const { return m_stack.empty(); }

        /**
         * @brief Returns the number of scenes in the stack.
         * @return The number of scenes.
         */
        [[nodiscard]] std::size_t size() const { return m_stack.size(); }

    private:
        using Factory = std::function<std::unique_ptr<Scene>()>;

        std::unordered_map<std::string, Factory> m_registry;
        std::stack<std::unique_ptr<Scene>> m_stack;
        std::optional<Transition> m_pendingTransition;

        /**
         * @brief Pushes a scene onto the stack immediately.
         * @param id The ID of the scene.
         * @param ctx The application context.
         */
        void push(const std::string &id, Core::AppContext &ctx);

        /**
         * @brief Pops a scene from the stack immediately.
         * @param ctx The application context.
         */
        void pop(Core::AppContext &ctx);

        /**
         * @brief Replaces the top scene immediately.
         * @param id The ID of the new scene.
         * @param ctx The application context.
         */
        void replace(const std::string &id, Core::AppContext &ctx);

        /**
         * @brief Constructs a scene instance from an ID.
         * @param id The scene ID.
         * @return A unique pointer to the constructed scene.
         */
        [[nodiscard]] std::unique_ptr<Scene> construct(const std::string &id) const;
    };

} // namespace Game::Scene
