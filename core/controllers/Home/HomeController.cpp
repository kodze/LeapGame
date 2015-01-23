#include "../../../include/Home.hpp"


HomeController::HomeController(RenderWindow *window, const string &name) : Controller(window, name)
{
}

HomeController::~HomeController()
{

}

int HomeController::eventManager(Event event)
{
    // Clic souris

    if (event.type == sf::Event::MouseButtonPressed)
    {
        // Clic droit
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (event.mouseButton.x >= WIDTH / 2 - 100 && event.mouseButton.x <= (WIDTH / 2 - 100) + 200 &&
                    event.mouseButton.y >= HEIGHT / 2 - 200 && event.mouseButton.y <= (HEIGHT / 2 - 200) + 100)
            {
                _kernel->loadModule(Controller::Game);
            }
        }
    }
}

int HomeController::display()
{
    RectangleShape rectangle(Vector2f(WIDTH / 2 - 100, HEIGHT / 2 - 50));
    rectangle.setPosition(Vector2f(WIDTH / 2 - 100, HEIGHT / 2 - 200));
    rectangle.setSize(sf::Vector2f(200, 100));
    rectangle.setFillColor(Color::Green);
    _window->draw(rectangle);
}