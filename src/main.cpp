#include <SFML/Graphics.hpp>

class Application
{
public:
    Application()
    {
        sf::Vector2u w_size_u = {1024, 768};
        sf::Vector2f w_size_f = static_cast<sf::Vector2f>(w_size_u);
        sf::FloatRect v_rect = sf::FloatRect({0.0f, 0.0f}, w_size_f);
        sf::Vector2f v_center = w_size_f / 2.0f;
        std::string title = "Rocket Builder";

        m_View = sf::View(v_rect);
        m_View.setCenter(v_center);
        m_Window.create(sf::VideoMode(w_size_u), title);
        m_Window.setView(m_View);
        m_Window.setFramerateLimit(60);
    }

    void Run()
    {
        Load();
        while (m_Window.isOpen())
        {
            sf::Time time = m_Clock.restart();
            ProcessEvents();
            Update(time.asSeconds());
            Render();
        }
        Unload();
    }

    void Shutdown()
    {
        m_Window.close();
    }

private:
    void Load() {}

    void ProcessEvents()
    {
        while (const std::optional event = m_Window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                Shutdown();
            }
            if (const auto &resized = event->getIf<sf::Event::Resized>())
            {
                OnResizedUpdateView(resized->size);
            }
        }
    }
    
    void OnResizedUpdateView(const sf::Vector2u n_size)
    {
        sf::Vector2f n_size_f = static_cast<sf::Vector2f>(n_size);
        m_View.setSize(n_size_f);
        m_View.setCenter(n_size_f / 2.0f);
        m_Window.setView(m_View);
    }

    void Update(const float dt) {}

    void Render()
    {
        m_Window.clear(sf::Color::Black);
        m_Window.display();
    }

    void Unload() {}

private:
    sf::View m_View;
    sf::Clock m_Clock;
    sf::RenderWindow m_Window;
};

int main()
{
    Application app;
    app.Run();
    return 0;
}