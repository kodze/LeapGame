#include "../../include/Controller.hpp"

Controller::Controller(RenderWindow *window, const string &name)
{
    _window = window;
    _name = name;
    cout << "-> Module " << _name << "loading." << endl;
}

Controller::~Controller()
{
}

const string& Controller::getName() const {
    return (_name);
}