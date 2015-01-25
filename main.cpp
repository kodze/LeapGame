#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "include/SFMLKernel.hpp"
#include "include/Leap.h"
#include "include/leap.hpp"

using namespace Leap;

int main()
{
    SampleListener listener;
    Controller controller;


    SFMLKernel kernel(&listener, &controller);
   // Have the sample listener receive events from the controller
   controller.enableGesture(Gesture::TYPE_SWIPE);
   controller.enableGesture(Gesture::TYPE_KEY_TAP);
   controller.addListener(listener);

   srandom(time(NULL));
   kernel.loop();

}
