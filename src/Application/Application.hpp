#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

namespace Game
{
    class Application
    {
    public:
        Application();
        ~Application() = default;
        void Run();
        void Shutdown();

    private:
        void ProcessEvent(const std::optional<sf::Event> &event);
        void Update(const float dt);
        void Render();

    private:
        sf::View m_View;
        sf::Clock m_Clock;
        sf::RenderWindow m_Window;
        const std::string m_WindowTitle{"Rocket Builder"};
        const sf::Vector2u m_DefaultWindowSize{1024, 768};
    };
}