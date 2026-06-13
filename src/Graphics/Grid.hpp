#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Drawable.hpp>

#pragma once
#include <SFML/Graphics.hpp>

namespace Game
{
    class Grid : public sf::Drawable
    {
    public:
        Grid(float spacing = 32.0f, int interval = 4);
        ~Grid() = default;
        sf::Vector2f getNearestVertex(sf::Vector2f v) const;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        int interval;
        float spacing;
        sf::Color minor;
        sf::Color major;
    };
}