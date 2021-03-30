#include "hardware.h"

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

    changeServoPosition(0);
    delay(5000);
    changeServoPosition(50);
    delay(5000);
    changeServoPosition(0);
   
}


int main()
{
    setup();
    testHardware();

}