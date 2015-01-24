#include "../../../include/Home.hpp"

#include <unistd.h>

HomeController::HomeController(RenderWindow *window, SFMLKernel *kernel, const string &name) : IController(window, kernel, name)
{
    if (!_backgroundImg.loadFromFile("res/img/backgroundHome.png"))
    {
        cerr << "-> " << _name << ": Loading Background Fail" << endl;
    }


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
                _kernel->loadModule(IController::Game);
            }
        }
    }
}

int HomeController::display()
{
    RectangleShape rectangle(Vector2f(WIDTH / 2 - 200, HEIGHT / 2 - 50));
    rectangle.setPosition(Vector2f(WIDTH / 2 - 200, HEIGHT / 2 - 200));
    rectangle.setSize(sf::Vector2f(400, 100));
    Color c;
    c.r = 176;
    c.g = 177;
    c.b = 181;
    rectangle.setFillColor(c);
    sf::Font font;
    font.loadFromFile("res/NAKED.ttf");
    // Create a text

    sf::Text txt("Play", font);
    txt.setPosition(Vector2f(WIDTH / 2 - 100, HEIGHT / 2 - 195));
    txt.setCharacterSize(80);
    txt.setStyle(sf::Text::Bold);
    txt.setColor(sf::Color::White);
    // Draw it

    Sprite text;

    text.setTexture(_backgroundImg);
    _window->draw(text);
    _window->draw(rectangle);
    _window->draw(txt);

    if (_kernel->_listener->nbHand == 2)
      _kernel->loadModule(IController::Game);

    
    //_window->draw(rectangle);
}
