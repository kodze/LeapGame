#ifndef __RESULTS_HPP__
# define __RESULTS_HPP__

#include <curl/curl.h>
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
    ResultsController(RenderWindow *window, SFMLKernel *kernel, const string &name, int score = 42);
    virtual ~ResultsController();
    int eventManager(Event event);
    int display();
    void getScore();
private:
    Texture _backgroundImg;
    vector<string> _result;
    int _score;
    string _pseudo;
    CURL		*_curl;
};


#endif