#ifndef __HOME_HPP__
# define __HOME_HPP__

#include "Leap.h"
#include "leap.hpp"
#include "SFMLKernel.hpp"
#include "IController.hpp"

using namespace std;
using namespace sf;
using namespace Leap;

class HomeController : public IController
{
public:
    HomeController(RenderWindow *window, SFMLKernel *kernel, const string &name);

    virtual ~HomeController();

    int eventManager(Event event);

    int display();

private:
  Sprite _background;
  Sprite _background2;
  Clock	_swapClock;
  bool	_isFirst;
};

#endif
