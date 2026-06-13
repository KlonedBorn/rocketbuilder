#include "Grid.hpp"
#include <cmath>

namespace Game
{
    Grid::Grid(float spacing, int interval)
        : spacing(spacing), interval(interval)
    {
        minor = sf::Color(255, 255, 255, static_cast<unsigned char>(255 * 0.12f));
        major = sf::Color(255, 255, 255, static_cast<unsigned char>(255 * 0.35f));
    }

    sf::Vector2f Grid::getNearestVertex(sf::Vector2f v) const
    {
        float snappedX = std::round(v.x / spacing) * spacing;
        float snappedY = std::round(v.y / spacing) * spacing;
        return {snappedX, snappedY};
    }

    void Grid::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        const sf::View &view = target.getView();
        sf::Vector2f center = view.getCenter();
        sf::Vector2f size = view.getSize();

        float left = center.x - size.x / 2.f;
        float right = center.x + size.x / 2.f;
        float top = center.y - size.y / 2.f;
        float bottom = center.y + size.y / 2.f;

        float startX = std::floor(left / spacing) * spacing;
        float endX = std::ceil(right / spacing) * spacing;
        float startY = std::floor(top / spacing) * spacing;
        float endY = std::ceil(bottom / spacing) * spacing;

        sf::VertexArray vertices(sf::PrimitiveType::Lines);

        for (float x = startX; x <= endX; x += spacing)
        {
            int gridIndex = static_cast<int>(std::round(x / spacing));
            sf::Color lineColor = (gridIndex % interval == 0) ? major : minor;

            sf::Vertex v1;
            v1.position = {x, top};
            v1.color = lineColor;

            sf::Vertex v2;
            v2.position = {x, bottom};
            v2.color = lineColor;

            vertices.append(v1);
            vertices.append(v2);
        }

        for (float y = startY; y <= endY; y += spacing)
        {
            int gridIndex = static_cast<int>(std::round(y / spacing));
            sf::Color lineColor = (gridIndex % interval == 0) ? major : minor;
            sf::Vertex v1;
            v1.position = {left, y};
            v1.color = lineColor;

            sf::Vertex v2;
            v2.position = {right, y};
            v2.color = lineColor;

            vertices.append(v1);
            vertices.append(v2);
        }

        target.draw(vertices, states);
    }
}