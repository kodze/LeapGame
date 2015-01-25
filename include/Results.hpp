#ifndef __RESULTS_HPP__
# define __RESULTS_HPP__

#include <curl/curl.h>
#include <vector>
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
private:
    Texture _backgroundImg;
    vector<string> _result;
    int _score;
    string _pseudo;
    CURL		*_curl;
};

bool replace(std::string& str, const std::string& from, const std::string& to);
static size_t WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp);
int Split(vector<string>& vecteur, string chaine, char separateur);

#endif