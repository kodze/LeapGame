#ifndef __SFMLKERNEL_HPP__
# define __SFMLKERNEL_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Controller.hpp"
#include "Home.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;


// Game configurations

# define GAME_NAME "WaterLeap"
# define WIDTH 1920
# define HEIGHT 1080

class SFMLKernel
{
public:
    SFMLKernel();
    int loop();
    void loadModule(Controller::Module module);
    virtual ~SFMLKernel();

private:
    RenderWindow *_window;
    Controller *_currentModule;
};

#endif