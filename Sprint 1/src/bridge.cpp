#include "bridge.h"
#include "hardware.h"

PI_THREAD(closeRightBarrier)
{
    for (unsigned int i = 100; i > 50; i -= 2)
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}
PI_THREAD(closeLeftBarrier)
{
    for (unsigned int i = 50; i < 100; i += 2)
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
    return 0;
}
PI_THREAD(openRightBarrier)
{
    for (unsigned int i = 100; i > 50; i -= 2)
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}
PI_THREAD(openLeftBarrier)
{
    for (unsigned int i = 50; i < 100; i += 2)
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
    return 0;
}

int openBridge()
{
    for (unsigned int i = 0; i < 50; i += 2)
    {
        changeServoPosition(SERV1, i);
        delay(200);
    }
    return 0;
}

int closeBridge()
{
    for (unsigned int i = 50; i > 0; i -= 2)
    {
        changeServoPosition(SERV1, i);
        delay(200);
    }
    return 0;
}

int closeBarriers()
{
    int rightBarrier = piThreadCreate(closeRightBarrier);
    int leftBarrier = piThreadCreate(closeLeftBarrier);

    delay(3000);

    if (leftBarrier == 0 && rightBarrier == 0)
        return 0;
    return 1;
}

int openBarriers()
{
    int rightBarrier = piThreadCreate(openRightBarrier);
    int leftBarrier = piThreadCreate(openLeftBarrier);

    delay(3000);

    if (leftBarrier == 0 && rightBarrier == 0)
        return 0;
    return 1;
}

void checkBoatDetection()
{
    int distanceFront = getCurrentDistance(TRIG1, ECHO1);
    int distanceBack = getCurrentDistance(TRIG2, ECHO2);

    if (distanceFront < 10 || distanceBack < 10)
    {
        if (closeBarriers() == 0)
            cout << "Barriers are closing!" << endl;

        if (openBridge() == 0)
            cout << "Bridge has been opened!" << endl;

        while (distanceFront < 10 || distanceBack < 10)
        {
            distanceFront = getCurrentDistance(TRIG1, ECHO1);
            distanceBack =  getCurrentDistance(TRIG2, ECHO2);
        }

        delay(5000);

        if (closeBridge() == 0)
            cout << "Bridge has been closed!" << endl;

        if (openBarriers() == 0)
            cout << "Barriers are opening!" << endl;
    }
}