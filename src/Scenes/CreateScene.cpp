#include "CreateScene.hpp"

namespace Game::Scenes
{
    CreateScene::CreateScene()
    {
    }

    void CreateScene::onLoad(Core::AppContext &context)
    {
    }

    void CreateScene::onEvent(Core::AppContext &context, const std::optional<sf::Event> &event)
    {
    }

    void CreateScene::onUpdate(Core::AppContext &context, sf::Time dt)
    {
    }

    void CreateScene::onRender(Core::AppContext &context, sf::RenderWindow &window)
    {
        window.draw(m_gridLayer);
    }

    void CreateScene::onUnload(Core::AppContext &context)
    {
    }
}
