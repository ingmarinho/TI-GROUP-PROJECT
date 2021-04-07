#include "hardware.h"
#include "bridge.h"
#include "boatmaster.h"

int main()
{
    setup();
    activateBoatTrafficLight(0);

    startBoatDetectionThread();

    receiveCommands();
    // sendCommands();
}