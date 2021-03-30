#include "bridge.h"
#include "hardware.h"

int openBridge()
{
    for (unsigned int i = 0; i < 50; i += 2)
    {
        changeServoPositionBridge(i);
        delay(200);
    }
    return 0;
}

int closeBridge()
{
    for (unsigned int i = 50; i > 0; i -= 2)
    {
        changeServoPositionBridge(i);
        delay(200);
    }
    return 0;
}

int openRightBarrier()
{
    for (unsigned int i = 100; i > 50; i -= 2)
    {
        changeServoPositionBarriers(SERV2, i);
        delay(200);
    }
    return 0;
}

int closeRightBarrier()
{
    for (unsigned int i = 50; i < 100; i += 2)
    {
        changeServoPositionBarriers(SERV2, i);
        delay(200);
    }
    return 0;
}

int openLeftBarrier()
{
    for (unsigned int i = 50; i < 100; i += 2)
    {
        changeServoPositionBarriers(SERV3, i);
        delay(200);
    }
    return 0;
}

int closeLeftBarrier()
{
    for (unsigned int i = 100; i > 50; i -= 2)
    {
        changeServoPositionBarriers(SERV3, i);
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
        if (closeRightBarrier() == 0 && closeLeftBarrier() == 0)
            cout << "Barriers are closing!" << endl;

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

        if (openRightBarrier() == 0 && openLeftBarrier() == 0)
            cout << "Barriers are opening!" << endl;

    }

}