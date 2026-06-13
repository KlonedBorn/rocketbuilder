#pragma once

#include <optional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

/**
 * @brief Forward declaration of AppContext.
 * 
 * AppContext is defined in Core/Application.hpp. The Scene module never owns or includes that definition.
 */
namespace Core { struct AppContext; }

namespace Game::Scene
{
    /**
     * @brief Abstract base class for all game scenes.
     */
    class Scene
    {
    public:
        virtual ~Scene() = default;

        /**
         * @brief Called when the scene is first loaded.
         * @param context The application context.
         */
        virtual void onLoad(Core::AppContext& context) = 0;

        /**
         * @brief Called when a window event occurs.
         * @param context The application context.
         * @param event The event that occurred.
         */
        virtual void onEvent(Core::AppContext& context, const std::optional<sf::Event>& event) = 0;

        /**
         * @brief Called every frame to update the scene state.
         * @param context The application context.
         * @param dt The time elapsed since the last frame.
         */
        virtual void onUpdate(Core::AppContext& context, sf::Time dt) = 0;

        /**
         * @brief Called every frame to render the scene.
         * @param context The application context.
         * @param window The render window.
         */
        virtual void onRender(Core::AppContext& context, sf::RenderWindow& window) = 0;

        /**
         * @brief Called when the scene is about to be unloaded.
         * @param context The application context.
         */
        virtual void onUnload(Core::AppContext& context) = 0;
    };

} // namespace Game::Scene
