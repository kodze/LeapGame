#ifndef __GAME_HPP__
# define __GAME_HPP__

#include "Controller.hpp"

using namespace std;
using namespace sf;

class GameController : public Controller
{
public:
    GameController(RenderWindow *window, const string &name);
    virtual ~GameController();

    int eventManager(Event event);
    int display();
};

#endif
