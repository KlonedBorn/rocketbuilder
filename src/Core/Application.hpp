#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#include "../Scene/SceneManager.hpp"

namespace Game::Core
{
    struct AppState
    {
    };

    /**
     * @brief Context object passed to scenes, containing references to global systems and state.
     */
    struct AppContext
    {
        AppState& state;
    };

    class Application
    {
    public:
        Application();
        ~Application() = default;
        void Run();
        void Shutdown();

    private:
        void ProcessEvents();
        void Update(sf::Time dt);
        void Render();

        AppState m_AppState;
        Scene::SceneManager m_SceneManager;

        sf::View m_View;
        sf::Clock m_Clock;
        sf::RenderWindow m_Window;
    };
}