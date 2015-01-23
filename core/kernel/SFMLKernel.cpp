#include "../../include/SFMLKernel.hpp"

SFMLKernel::SFMLKernel()
{
    _window = new RenderWindow(sf::VideoMode(WIDTH, HEIGHT), GAME_NAME);
    _currentModule = new GameController(_window, "Home");
    cout << "-> SFML initialisation : Done." << endl;
}

void SFMLKernel::loadModule(Controller::Module module)
{
    Controller *tmp;

    tmp = _currentModule;

    switch (module)
    {
        case Controller::Home:
            _currentModule = new HomeController(_window, "Home");
            break;

        case Controller::Game:
            _currentModule = new GameController(_window, "Game");
            break;
    }
    delete(tmp);
}

int SFMLKernel::loop()
{
    cout << "-> Loop started: " << endl;

    while (_window->isOpen())
    {
        Event event;

        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window->close();
            _currentModule->eventManager(event);
        }
        _window->clear();
        _currentModule->display();
        _window->display();
    }
}

SFMLKernel::~SFMLKernel()
{
}