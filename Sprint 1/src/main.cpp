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

    for (unsigned int i = 0; i < 100; i += 2)
    {
        changeServoPosition(i);
        delay(200);
    }

    for (unsigned int j = 100; j > 0; j -= 2)
    {
        changeServoPosition(i);
        delay(200);
    }
}

int openBridge()
{
    for (unsigned int i = 0; i < 100; i += 2)
    {
        changeServoPosition(i);
        delay(200);
    }
    return 0;
}

int closeBridge()
{
    for (unsigned int j = 100; j > 0; j -= 2)
    {
        changeServoPosition(i);
        delay(200);
    }
    return 0;
}

void checkBoatDetection()
{
    int distance = getCurrentDistance();
    if (distance < 100)
    {
        if (openBridge() == 0)
            cout << "Bridge has been opened!" << endl;
            
        while (distance < 100)
        {
            distance = getCurrentDistance();
            delay(1000);
        }

        if (closeBridge() == 0)
            cout << "Bridge has been closed!" << endl;
    }

}

int main()
{
    setup();
    testHardware();
    while (true)
    {
        checkBoatDetection();
    }
}