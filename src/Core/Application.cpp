#include "Application.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
#include <format>

namespace Game::Core
{
    Application::Application()
    {
        sf::Vector2u defaultWindowSize = {1024, 768};
        m_Window.create(sf::VideoMode(defaultWindowSize), "Rocket Builder");
        m_Window.setFramerateLimit(60);
        m_Window.setVerticalSyncEnabled(true);

        sf::Vector2f viewSize = static_cast<sf::Vector2f>(defaultWindowSize);
        m_View.setSize(viewSize);
        m_View.setCenter(viewSize / 2.0f);
        m_Window.setView(m_View);

        if (!ImGui::SFML::Init(m_Window))
        {
            std::cerr << "Dear ImGUI failed to initialize" << std::endl;
            Shutdown();
        }

        m_SceneManager.registerScene()
    }

    void Application::Run()
    {
        while (m_Window.isOpen())
        {
            sf::Time time = m_Clock.restart();
            ProcessEvents();

            ImGui::SFML::Update(m_Window, time);
            Update(time.asSeconds());

            m_Window.clear(sf::Color::Black);
            Render();
            ImGui::SFML::Render(m_Window);
            m_Window.display();
        }
    }

    void Application::Shutdown()
    {
        m_Window.close();
    }

    void Application::ProcessEvents()
    {
        while (const std::optional event = m_Window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(m_Window, event);
            if (event->is<sf::Event::Closed>())
            {
                Shutdown();
            }
            if (const auto &resized = event->getIf<sf::Event::Resized>())
            {
                sf::Vector2f n_size_f = static_cast<sf::Vector2f>(resized->size);
                m_View.setSize(n_size_f);
                m_View.setCenter(n_size_f / 2.0f);
                m_Window.setView(m_View);
            }
        }
    }

    void Application::Update(const float dt)
    {
    }

    void Application::Render()
    {
    }
}