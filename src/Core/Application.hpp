#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

namespace Game::Core
{
    class Application
    {
    public:
        Application();
        ~Application() = default;
        void Run();
        void Shutdown();

    private:
        void ProcessEvents();
        void Update(const float dt);
        void Render();

    private:
        sf::View m_View;
        sf::Clock m_Clock;
        sf::RenderWindow m_Window;
    };
}