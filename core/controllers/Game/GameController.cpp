#include "../../../include/Game.hpp"


GameController::GameController(RenderWindow *window, SFMLKernel *kernel, const string &name) : Controller(window, kernel, name)
{
}

GameController::~GameController()
{

}

int GameController::eventManager(Event event)
{
}

int GameController::display()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Magenta);
    _window->draw(shape);
}