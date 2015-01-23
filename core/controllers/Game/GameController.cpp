#include "../../../include/Game.hpp"


GameController::GameController(RenderWindow *window, const string &name) : Controller(window, name)
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