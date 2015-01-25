#ifndef __RESULTS_HPP__
# define __RESULTS_HPP__

#include "Leap.h"
#include "leap.hpp"
#include "SFMLKernel.hpp"
#include "IController.hpp"

using namespace std;
using namespace sf;
using namespace Leap;

class ResultsController : public IController
{
public:
    ResultsController(RenderWindow *window, SFMLKernel *kernel, const string &name);
    virtual ~ResultsController();
    int eventManager(Event event);
    int display();

private:
    Texture _backgroundImg;
};


#endif