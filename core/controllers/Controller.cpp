#include "../../include/Controller.hpp"

Controller::Controller(RenderWindow *window, SFMLKernel *kernel, const string &name)
{
    _window = window;
    _name = name;
    _kernel = kernel;
    cout << "-> Module " << _name << "loading." << endl;
}

Controller::~Controller()
{
}

const string& Controller::getName() const {
    return (_name);
}