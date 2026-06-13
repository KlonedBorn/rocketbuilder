#pragma once

#include "../Scene/Scene.hpp"
#include "../Graphics/Grid.hpp"

namespace Game::Scenes
{
    /**
     * @brief The main editor scene where rocket building takes place.
     */
    class EditorScene : public Scene::Scene
    {
    public:
        /**
         * @brief Constructs the EditorScene.
         */
        EditorScene();

        /**
         * @brief Destroys the EditorScene.
         */
        ~EditorScene() override = default;

        /**
         * @brief Called when the editor scene is loaded.
         * @param context The application context.
         */
        void onLoad(Core::AppContext& context) override;

        /**
         * @brief Handles window events for the editor scene.
         * @param context The application context.
         * @param event The event to handle.
         */
        void onEvent(Core::AppContext& context, const std::optional<sf::Event>& event) override;

        /**
         * @brief Updates the editor scene state.
         * @param context The application context.
         * @param dt Time elapsed since the last frame.
         */
        void onUpdate(Core::AppContext& context, sf::Time dt) override;

        /**
         * @brief Renders the editor scene.
         * @param context The application context.
         * @param window The render window.
         */
        void onRender(Core::AppContext& context, sf::RenderWindow& window) override;

        /**
         * @brief Called when the editor scene is unloaded.
         * @param context The application context.
         */
        void onUnload(Core::AppContext& context) override;

    private:
        Graphics::Grid m_gridLayer;
    };
}
