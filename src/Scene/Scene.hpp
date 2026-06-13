#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "../Core/AppData.hpp"

namespace Game::Scene
{
    class Scene
    {
    public:
        virtual void onLoad(AppData &data) = 0;
        virtual void onEvent(AppData &data, const std::optional<sf::Event> &event) = 0;
        virtual void onUpdate(AppData &data, const sf::Time dt) = 0;
        virtual void onRender(AppData &data, sf::RenderWindow &window) = 0;
        virtual void onUnload(AppData &data) = 0;
    };
}