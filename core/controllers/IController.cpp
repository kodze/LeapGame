#include "IController.hpp"

IController::IController(RenderWindow *window, SFMLKernel *kernel, const string &name)
{
    _window = window;
    _name = name;
    _kernel = kernel;
    cout << "-> Module " << _name << "loading." << endl;
}

IController::~IController()
{
}

const string&IController::getName() const {
    return (_name);
}