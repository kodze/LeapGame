#ifndef __CONTROLLER_HPP__
# define __CONTROLLER_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Leap.h"

class SFMLKernel;

using namespace Leap;
using namespace std;
using namespace sf;

class IController
{
public:
    enum Module
    {
        Home,
        Game
    };

    IController(RenderWindow *window, SFMLKernel *kernel, const string &name);
    virtual ~IController();

    virtual int eventManager(Event event) = 0;
    virtual int display() = 0;
    virtual const string &getName() const;
protected:
    string _name;
    RenderWindow *_window;
    SFMLKernel *_kernel;
};

#endif