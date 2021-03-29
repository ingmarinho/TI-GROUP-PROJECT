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

    if (servo(80) == 0)
        cout << "Servo set to: 80%" << endl;
    
}


int main()
{
    setup();
    testHardware();

}