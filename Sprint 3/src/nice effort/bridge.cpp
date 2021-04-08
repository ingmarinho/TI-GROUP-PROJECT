#include "bridge.h"
#include "hardware.h"

using namespace std;

PI_THREAD(closeRightBarrier) // Code om de rechter slagboomd dicht te zetten.
{
    for (unsigned int i = 100; i > 50; i -= 2) // Zorgt voor de stepsize van de servo voor een 'vloeiende beweging'
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}

void closeLeftBarrier() // Code om de linker slagboom dicht te zetten.
{
    for (unsigned int i = 50; i < 100; i += 2) //  Zorgt voor de stepsize van de servo voor een 'vloeiende beweging'
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
}

PI_THREAD(openRightBarrier) // code om de rechter slagboom open te zetten.
{
    for (unsigned int i = 50; i < 100; i += 2) //  Zorgt voor de stepsize van de servo voor een 'vloeiende beweging'
    {
        changeServoPosition(SERV2, i);
        delay(200);
    }
    return 0;
}

void openLeftBarrier() // Code om de rechter slagboom open te zetten.
{
    for (unsigned int i = 100; i > 50; i -= 2) // Zorgt voor de stepsize van de servo voor een 'vloeiende beweging'
    {
        changeServoPosition(SERV3, i);
        delay(200);
    }
}

PI_THREAD(activateTrafficLights) // Thread voor de gevaren lichten op de brug.
{
    while (sequenceStart == 0) // ga door tot dat je uit word gezet.
    {
        activateLeds(); // laat de lamen uit en aan gaan.
        delay(200);
    }
    return 0;
}

void openBridge() // Code om de brug te openen.
{
    for (unsigned int i = 0; i < 50; i += 2) // Zorgt voor de stepsize van de servo voor een 'vloeiende beweging'
    {
        changeServoPosition(SERV1, i);
        delay(200);
    }
}

void closeBridge() // Code om de brug te sluiten.
{
    for (unsigned int i = 50; i > 0; i -= 2) //  Zorgt voor de stepsize van de servo voor een 'vloeiende beweging'
    {
        changeServoPosition(SERV1, i);
        delay(200);
    }
}

int closeBarriers() // Code om beide slagebomen dicht te laten gaan.
{
    int rightBarrier = piThreadCreate(closeRightBarrier); // Zet de rechter slagboom in zijn eigen thread.
    closeLeftBarrier(); // stuur de linker aan.

    if (rightBarrier == 0) // Kijk of de slagboom in zijn beginpositie staat.
        return 0;
    return -1;
}

int openBarriers() // Code om beide slagbomen te openen.
{
    int rightBarrier = piThreadCreate(openRightBarrier); // Zet de rechter slagboom in zijn eigen thread.
    openLeftBarrier(); // Stuurt de linker slagboom aan.

    if (rightBarrier == 0)  // Kijk of de de slagboom in zijn beginpostitie staat.
        return 0;
    return -1;
}

void playBarrierSound() // Code om het piepertje geluid uit te laten voeren bij openen en sluiten van slagbomen. 
{
    for (unsigned int i = 0; i < 5; i++)
    {
        barrierSound();
        delay(200);
    }
}

void startBridgeSequence() // Code om de functionaliteiten van de brug uit te voeren.
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

PI_THREAD(checkBoatDetection) // Thread om beide afstandssensoren gelijkwaardig input te laten meten.
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
