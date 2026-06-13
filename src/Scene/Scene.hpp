#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

using namespace Game;

namespace Core
{
    struct AppContext;
}

namespace Game::Scene
{
    class Scene
    {
    public:
        virtual void onLoad(Core::AppContext &context) = 0;
        virtual void onEvent(Core::AppContext &context, const std::optional<sf::Event> &event) = 0;
        virtual void onUpdate(Core::AppContext &context, const sf::Time dt) = 0;
        virtual void onRender(Core::AppContext &context, sf::RenderWindow &window) = 0;
        virtual void onUnload(Core::AppContext &context) = 0;
    };
}