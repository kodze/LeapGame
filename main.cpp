#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "include/SFMLKernel.hpp"

int main()
{
    SFMLKernel kernel;

    srandom(time(NULL));
    kernel.loop();
}
