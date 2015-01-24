#ifndef __SFMLKERNEL_HPP__
# define __SFMLKERNEL_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Leap.h"
#include "leap.hpp"
#include "IController.hpp"
#include "Home.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;
using namespace Leap;

// Game configurations

# define GAME_NAME "WaterLeap"
# define WIDTH 1920
# define HEIGHT 1080

class SFMLKernel
{
public:
    SFMLKernel(SampleListener *listener, Controller *controller);
    int loop();
    void loadModule(IController::Module module);
    virtual ~SFMLKernel();
    SampleListener *_listener;
    Controller *_controller;

private:
    RenderWindow *_window;
    IController *_currentModule;
};

#endif