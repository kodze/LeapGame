#ifndef __CONTROLLER_HPP__
# define __CONTROLLER_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

class SFMLKernel;

using namespace std;
using namespace sf;

class Controller
{
public:
    enum Module
    {
        Home,
        Game
    };

    Controller(RenderWindow *window, const string &name);
    virtual ~Controller();

    virtual int eventManager(Event event) = 0;
    virtual int display() = 0;
    virtual const string &getName() const;

protected:
    string _name;
    RenderWindow *_window;
    SFMLKernel *_kernel;
};

#endif