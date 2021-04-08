#include "hardware.h"
#include "bridge.h"
#include "boatmaster.h"

int main()
{
    setup();                            // Zet alle pinnen goed.
    activateBoatTrafficLight(0);        // Zorg ervoor dat het stoplicht voor de boten standaard op rood staat.
    checkBoatDetection();               // Start de main loop die continu checkt of er een boot binnen bereik is.
}