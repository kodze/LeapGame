#ifndef __HOME_HPP__
# define __HOME_HPP__

#include "SFMLKernel.hpp"
#include "Controller.hpp"

using namespace std;
using namespace sf;

class HomeController : public Controller
{
public:
    HomeController(RenderWindow *window, const string &name);
    virtual ~HomeController();

    int eventManager(Event event);
    int display();
};

#endif