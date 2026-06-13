#pragma once

#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

// Forward declaration only — AppContext is defined in Core/Application.hpp.
// The /Scene module never owns or includes that definition.
namespace Core { struct AppContext; }

namespace Game::Scene
{
    class Scene
    {
    public:
        virtual ~Scene() = default;

        virtual void onLoad(Core::AppContext& context) = 0;
        virtual void onEvent(Core::AppContext& context, const std::optional<sf::Event>& event) = 0;
        virtual void onUpdate(Core::AppContext& context, sf::Time dt) = 0;
        virtual void onRender(Core::AppContext& context, sf::RenderWindow& window) = 0;
        virtual void onUnload(Core::AppContext& context) = 0;
    };

} // namespace Game::Scene