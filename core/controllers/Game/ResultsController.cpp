#include "../../../include/Results.hpp"


ResultsController::ResultsController(RenderWindow *window, SFMLKernel *kernel, const string &name) : IController(window, kernel, name)
{
    if (!_backgroundImg.loadFromFile("res/img/backgroundHome.png"))
    {
        cerr << "-> " << _name << ": Loading Background Fail" << endl;
    }


}

ResultsController::~ResultsController()
{

}

int ResultsController::eventManager(Event event)
{
}

int ResultsController::display()
{
    Sprite text;

    text.setTexture(_backgroundImg);
    _window->draw(text);
}
