#include "bridge.h"
#include "hardware.h"

using namespace std;

PI_THREAD(closeRightBarrier)
{
    for (unsigned int i = 100; i > 50; i -= 2)
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}
void closeLeftBarrier()
{
    for (unsigned int i = 50; i < 100; i += 2)
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
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
void openLeftBarrier()
{
    for (unsigned int i = 100; i > 50; i -= 2)
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
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

void openBridge()
{
    for (unsigned int i = 0; i < 50; i += 2)
    {
        changeServoPosition(SERV1, i);
        delay(200);
    }
}

void closeBridge()
{
    for (unsigned int i = 50; i > 0; i -= 2)
    {
        changeServoPosition(SERV1, i);
        delay(200);
    }
}

int closeBarriers()
{
    int rightBarrier = piThreadCreate(closeRightBarrier);
    closeLeftBarrier();

    if (rightBarrier == 0)
        return 0;
    return -1;
}

int openBarriers()
{
    int rightBarrier = piThreadCreate(openRightBarrier);
    openLeftBarrier();

    if (rightBarrier == 0)
        return 0;
    return -1;
}

void playBarrierSound()
{
    for (unsigned int i = 0; i < 5; i++)
    {
        barrierSound();
        delay(200);
    }
}

void startBridgeSequence()
{
    sequenceStart = 0;
    
    int distanceFront = 0;
    int distanceBack = 0;

    int trafficLights = piThreadCreate(activateTrafficLights);

    delay(3000);

    playBarrierSound();

    delay(1000);

    openBarriers();
    cout << "Barriers are closing!" << endl;
    
    delay (5000);

    openBridge();
    cout << "Bridge has been opened!" << endl;

    activateBoatTrafficLight(1);

    while (distanceFront < 10 || distanceBack < 10)
    {
        distanceFront = getCurrentDistance(TRIG1, ECHO1);
        distanceBack = getCurrentDistance(TRIG2, ECHO2);
    }

    delay(5000);

    activateBoatTrafficLight(0);

    closeBridge();
    cout << "Bridge has been closed!" << endl;

    delay(1000);

    playBarrierSound();

    closeBarriers();
    cout << "Barriers are opening!" << endl;

    delay(3000);

    sequenceStart = 1;
}

PI_THREAD(checkBoatDetection)
{
    while (true)
    {
        int distanceFront = getCurrentDistance(TRIG1, ECHO1);
        int distanceBack = getCurrentDistance(TRIG2, ECHO2);

        if (distanceFront < 10 || distanceBack < 10)
            startBridgeSequence();
    }
    return 0;
}


void startBoatDetectionThread()
{
    int x = piThreadCreate(checkBoatDetection);
}

void checkBoatDetection()
{
    while (true)
    {
        int distanceFront = getCurrentDistance(TRIG1, ECHO1);
        int distanceBack = getCurrentDistance(TRIG2, ECHO2);

        if (distanceFront < 10 || distanceBack < 10)
            startBridgeSequence();
    }
}