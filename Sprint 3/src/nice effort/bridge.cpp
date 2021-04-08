#include "bridge.h"
#include "hardware.h"

using namespace std;

PI_THREAD(closeRightBarrier) // code om de rechter slagboom omhoog te zetten.
{
    for (unsigned int i = 100; i > 50; i -= 2) // er voor zorgen dat de slagboom langzaam beweegt.
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}

void closeLeftBarrier() // code om de linker slagboom omhoog te zetten.
{
    for (unsigned int i = 50; i < 100; i += 2) // er voor zorgen dat de slagboom langzaam beweegt.
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
}

PI_THREAD(openRightBarrier) // code om de rechter slagboom horizontaal te zetten.
{
    for (unsigned int i = 50; i < 100; i += 2) // er voor zorgen dat de slagboom langzaam beweegt.
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}

void openLeftBarrier() // code om de rechter slagboom horizontaal te zetten.
{
    for (unsigned int i = 100; i > 50; i -= 2) // er voor zorgen dat de slagboom langzaam beweegt.
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
}

PI_THREAD(activateTrafficLights) // code voor de lampen voor de weg aan te sturen.
{
    while (sequenceStart == 0) // ga door tot dat je uit word gezet.
    {
        activateLeds(); // laat de lamen uit en aan gaan.
        delay(200);
    }
    return 0;
}

void openBridge() // code om de brug te openen.
{
    for (unsigned int i = 0; i < 50; i += 2) // er voor zorgen dat de brug niet te snel open gaat.
    {
        changeServoPosition(SERV1, i);
        delay(200);
    }
}

void closeBridge() // code om de brug te sluiten.
{
    for (unsigned int i = 50; i > 0; i -= 2) // er voor zorgen dat de brug niet te snel dicht gaat.
    {
        changeServoPosition(SERV1, i);
        delay(200);
    }
}

int closeBarriers() // stuur bijde slagbomen naar een verticale positie.
{
    int rightBarrier = piThreadCreate(closeRightBarrier); // zet de rechter slagboom in zijn eigen thread.
    closeLeftBarrier(); // stuur de linker aan.

    if (rightBarrier == 0) // kijk of de rechter barriere verticaal is.
        return 0;
    return -1;
}

int openBarriers() // stuur bijde slagbomen naar een horizontale positie.
{
    int rightBarrier = piThreadCreate(openRightBarrier); // zet de rechter slagboom in zijn eigen thread.
    openLeftBarrier(); // stuur de linker aan.

    if (rightBarrier == 0)  // kijk of de rechter barriere horizontaal is.
        return 0;
    return -1;
}

void playBarrierSound() // 
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