#include "hardware.h"

void testHardware()
{
    int x = 0;
    while (x < 20)
    {
        int distance = distanceSensor();
        cout << "Distance in cm: " << distance << endl;
        delay(500);
        x++;
    }
    
    // servo(90);
}

int main()
{
    setup();
    testHardware();
}