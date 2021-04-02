#include "hardware.h"
#include "bridge.h"


int main()
{
    setup();
    activateBoatTrafficLight(0);

    while (true)
    {
        checkBoatDetection();
    }
}