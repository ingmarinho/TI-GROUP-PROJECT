#include "hardware.h"
#include "bridge.h"

void testHardware()
{
    int x = 0;
    while (x < 20)
    {
        int distance = getCurrentDistance();
        cout << "Distance in cm: " << distance << endl;
        delay(500);
        x++;
    }

    for (unsigned int i = 0; i < 50; i += 2)
    {
        changeServoPosition(i);
        delay(200);
    }

    for (unsigned int j = 50; j > 0; j -= 2)
    {
        changeServoPosition(j);
        delay(200);
    }
}

int main()
{
    setup();
    // testHardware();
    while (true)
    {
        checkBoatDetection();
    }
}