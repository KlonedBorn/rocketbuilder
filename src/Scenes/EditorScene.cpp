#include "EditorScene.hpp"

namespace Game::Scenes
{
    EditorScene::EditorScene()
    {
    }

    void EditorScene::onLoad(Core::AppContext &context)
    {
    }

    void EditorScene::onEvent(Core::AppContext &context, const std::optional<sf::Event> &event)
    {
    }

    void EditorScene::onUpdate(Core::AppContext &context, sf::Time dt)
    {
    }

    void EditorScene::onRender(Core::AppContext &context, sf::RenderWindow &window)
    {
        window.draw(m_gridLayer);
    }

    void EditorScene::onUnload(Core::AppContext &context)
    {
    }
}
