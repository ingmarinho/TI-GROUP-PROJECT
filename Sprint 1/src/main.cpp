#include "hardware.h"

void testHardware()
{
    // int x = 0;
    // while (x < 20)
    // {
    //     int distance = getCurrentDistance();
    //     cout << "Distance in cm: " << distance << endl;
    //     delay(500);
    //     x++;
    // }

    // changeServoPosition(1);
    softServoWrite(SERV, 500)
}


int main()
{
    setup();
    testHardware();
}