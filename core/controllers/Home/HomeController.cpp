#include "../../../include/Home.hpp"

#include <unistd.h>

HomeController::HomeController(RenderWindow *window, SFMLKernel *kernel, const string &name) : IController(window, kernel, name), _isFirst(true)
{
  sf::Image     tmp;
  tmp.loadFromFile("res/img_home/background.jpg");
  sf::Texture *tex = new sf::Texture();
  tex->loadFromImage(tmp);
  _background.setTexture(*tex);
  
  sf::Image     tmp2;
  tmp2.loadFromFile("res/img_home/background2.jpg");
  sf::Texture *tex2 = new sf::Texture();
  tex2->loadFromImage(tmp2);
  _background2.setTexture(*tex2);
}

HomeController::~HomeController()
{

}

int HomeController::eventManager(Event event)
{}

int HomeController::display()
{

  if (_kernel->_listener->nbHand == 2)
    _kernel->loadModule(IController::Game);

  if (_isFirst)
    _window->draw(_background);
  else
    _window->draw(_background2);
  if (_swapClock.getElapsedTime().asSeconds() >= 0.5f)
    {
      _isFirst = !_isFirst;
      _swapClock.restart();
    }
}
