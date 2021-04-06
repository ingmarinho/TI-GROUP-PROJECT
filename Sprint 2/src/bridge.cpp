#include "bridge.h"
#include "hardware.h"

static volatile bool sequenceStart = 0;
int bridge_open_counter = 0;

PI_THREAD(closeRightBarrier)
{
    for (unsigned int i = 100; i > 50; i -= 2)
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}
int closeLeftBarrier()
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
    for (unsigned int i = 50; i < 100; i += 2)
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}
int openLeftBarrier()
{
    for (unsigned int i = 100; i > 50; i -= 2)
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
    return 0;
}

PI_THREAD(activateTrafficLights)
{
    while (sequenceStart == 0)
    {
        activateLeds();
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
    int leftBarrier = closeLeftBarrier();

    if (leftBarrier == 0 && rightBarrier == 0)
        return 0;
    return 1;
}

int openBarriers()
{
    int rightBarrier = piThreadCreate(openRightBarrier);
    int leftBarrier = openLeftBarrier();

    if (leftBarrier == 0 && rightBarrier == 0)
        return 0;
    return 1;
}

int playBarrierSound()
{
    for (unsigned int i = 0; i < 5; i++)
    {
        barrierSound();
        delay(200);

    }
    return 0; 
}



void startBridgeSequence(int &distanceFront, int &distanceBack)
{ 
    sequenceStart = 0;

    int trafficLights = piThreadCreate(activateTrafficLights);

    delay(3000);

    playBarrierSound();

    delay(1000);

    if (openBarriers() == 0)
        cout << "Barriers are closing!" << endl;

    bridge_open_counter ++;

    if (openBridge() == 0)
        cout << "Bridge has been opened! Total times: " << bridge_open_counter << endl;
    
    activateBoatTrafficLight(1);

    while (distanceFront < 10 || distanceBack < 10)
    {
        distanceFront = getCurrentDistance(TRIG1, ECHO1);
        distanceBack = getCurrentDistance(TRIG2, ECHO2);
    }

    delay(5000);

    activateBoatTrafficLight(0);

    if (closeBridge() == 0)
        cout << "Bridge has been closed!" << endl;

    delay(1000);

    playBarrierSound();

    if (closeBarriers() == 0)
        cout << "Barriers are opening!" << endl;

    delay(3000);

    sequenceStart = 1;
}

void checkBoatDetection()
{
    int distanceFront = getCurrentDistance(TRIG1, ECHO1);
    int distanceBack = getCurrentDistance(TRIG2, ECHO2);

    if (distanceFront < 10 || distanceBack < 10)
        startBridgeSequence(distanceFront, distanceBack);
}