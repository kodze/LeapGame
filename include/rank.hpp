#ifndef __RANK_HPP__
# define __RANK_HPP__

#include <curl/curl.h>
#include "Leap.h"
#include "leap.hpp"
#include "SFMLKernel.hpp"

#include "IController.hpp"

using namespace std;
using namespace sf;
using namespace Leap;

class RankController : public IController
{
public:
    RankController(RenderWindow *window, SFMLKernel *kernel, const string &name, int score = 42);
    virtual ~RankController();
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