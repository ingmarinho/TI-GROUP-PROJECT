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


    for (unsigned int i = 0; i < 100; i++)
    {
        changeServoPosition(i);
        delay(100);
    }
   
}


int main()
{
    setup();
    testHardware();

}