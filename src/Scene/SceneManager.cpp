#include "SceneManager.hpp"

namespace Game::Scene
{
    // ── Transition requests (called by Application) ───────────────────────────

    void SceneManager::requestPush(const std::string &id)
    {
        m_pendingTransition = Transition{Transition::Kind::Push, id};
    }

    void SceneManager::requestPop()
    {
        m_pendingTransition = Transition{Transition::Kind::Pop, {}};
    }

    void SceneManager::requestReplace(const std::string &id)
    {
        m_pendingTransition = Transition{Transition::Kind::Replace, id};
    }

    void SceneManager::flushTransition(Core::AppContext &ctx)
    {
        if (!m_pendingTransition.has_value())
            return;

        // Take and clear before executing so that onLoad() of the incoming
        // scene can safely queue a further transition for the next frame.
        const auto transition = *m_pendingTransition;
        m_pendingTransition.reset();

        switch (transition.kind)
        {
        case Transition::Kind::Push:
            push(transition.sceneId, ctx);
            break;
        case Transition::Kind::Pop:
            pop(ctx);
            break;
        case Transition::Kind::Replace:
            replace(transition.sceneId, ctx);
            break;
        }
    }

    // ── Internal stack operations ─────────────────────────────────────────────

    std::unique_ptr<Scene> SceneManager::construct(const std::string &id) const
    {
        auto it = m_registry.find(id);
        if (it == m_registry.end())
            throw std::runtime_error("SceneManager: unknown scene id: \"" + id + "\"");

        return it->second();
    }

    void SceneManager::push(const std::string &id, Core::AppContext &ctx)
    {
        auto scene = construct(id);
        scene->onLoad(ctx);
        m_stack.push(std::move(scene));
    }

    void SceneManager::pop(Core::AppContext &ctx)
    {
        if (m_stack.empty())
            throw std::runtime_error("SceneManager: pop() on empty stack");

        m_stack.top()->onUnload(ctx);
        m_stack.pop();
    }

    void SceneManager::replace(const std::string &id, Core::AppContext &ctx)
    {
        if (!m_stack.empty())
            pop(ctx);

        push(id, ctx);
    }

    // ── Lifecycle forwarding ──────────────────────────────────────────────────

    void SceneManager::onEvent(Core::AppContext &ctx, const std::optional<sf::Event> &event)
    {
        if (!m_stack.empty())
            m_stack.top()->onEvent(ctx, event);
    }

    void SceneManager::onUpdate(Core::AppContext &ctx, sf::Time dt)
    {
        if (!m_stack.empty())
            m_stack.top()->onUpdate(ctx, dt);
    }

    void SceneManager::onRender(Core::AppContext &ctx, sf::RenderWindow &window)
    {
        if (!m_stack.empty())
            m_stack.top()->onRender(ctx, window);
    }

} // namespace Game::Scene