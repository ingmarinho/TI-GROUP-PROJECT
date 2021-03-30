#include "bridge.h"
#include "hardware.h"

int openBridge()
{
    for (unsigned int i = 0; i < 50; i += 2)
    {
        changeServoPosition(i);
        delay(200);
    }
    return 0;
}

int closeBridge()
{
    for (unsigned int i = 50; i > 0; i -= 2)
    {
        changeServoPosition(i);
        delay(200);
    }
    return 0;
}

void checkBoatDetection()
{
    int distanceFront = getCurrentDistanceFront();
    int distanceBack = getCurrentDistanceBack();

    if (distanceFront < 10 || distanceBack < 10)
    {
        if (openBridge() == 0)
            cout << "Bridge has been opened!" << endl;

        while (distanceFront < 10 || distanceBack < 10)
        {
            distanceFront = getCurrentDistanceFront();
            distanceBack = getCurrentDistanceBack();
        }

        delay(5000);

        if (closeBridge() == 0)
            cout << "Bridge has been closed!" << endl;
    }

}