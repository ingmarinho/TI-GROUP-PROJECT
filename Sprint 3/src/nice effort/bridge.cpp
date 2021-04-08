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

void playBarrierSound() // laat de bellen 5 keer klinken.
{
    for (unsigned int i = 0; i < 5; i++)
    {
        barrierSound();
        delay(200);
    }
}

void startBridgeSequence() // laat de brug open en dight gaan.
{
    sequenceStart = 0; // variable die laat zien aan de weg lampen dat ze nog bezig moeten zijn.
    
    int distanceFront = 0; // intitaleseer deze variables
    int distanceBack = 0;

    int trafficLights = piThreadCreate(activateTrafficLights); // maak een thread aan voor de waarschuwings lampen van de auto's

    delay(3000); // wacht even zodat mensen kunnen stoppen.

    playBarrierSound(); // laat het geluid 5 maal klinken.

    delay(1000); // wacht even tot het goede moment.

    openBarriers(); // maak de slagbomen horizontaal.
    cout << "Barriers are closing!" << endl; // wij gaan niet onze fout erkennen....
    
    delay (5000); // wacht even zodat ook le laaste gekken weg zijn.

    openBridge(); // open de brug
    cout << "Bridge has been opened!" << endl;

    activateBoatTrafficLight(1); // maak de ledstrip (voor de boten) groen.

    while (distanceFront < 10 || distanceBack < 10) // blijft open tot dat de boten buiten de 10 cm komen.
    {
        distanceFront = getCurrentDistance(TRIG1, ECHO1);
        distanceBack = getCurrentDistance(TRIG2, ECHO2);
    }

    delay(5000); // geef de boten even de tijd om langs de brug te gaan.

    activateBoatTrafficLight(0); // maak de ledstrip (voor de boten) rood.

    closeBridge(); // sluit de brug.
    cout << "Bridge has been closed!" << endl;

    delay(1000); // wacht tot dat de brug weer goed stil staat.

    playBarrierSound(); // laat het geluid weer 5 keer klinken.

    closeBarriers(); // zet de slagbomen verticaal.
    cout << "Barriers are opening!" << endl;

    delay(3000); // wacht even voor de singalen voor de auto's uit gaan.

    sequenceStart = 1; // zet de kniper lichten voor de auto's uit.
}

PI_THREAD(checkBoatDetection) // thread versie van de boot detectie.
{
    while (true) // bijft dit doen, voor altijd
    {
        int distanceFront = getCurrentDistance(TRIG1, ECHO1); // krijg de afstand van de 2 afstand sensors.
        int distanceBack = getCurrentDistance(TRIG2, ECHO2);

        if (distanceFront < 10 || distanceBack < 10) // als de afstand van 1 van de 2 binnen 10 valt laat dan de brug open en dight gaan.
            startBridgeSequence();
    }
    return 0;
}


void startBoatDetectionThread() // activeer de thread versie van de boot detectie.
{
    int x = piThreadCreate(checkBoatDetection);
}

void checkBoatDetection() // de linieare versie van de boot detectie.
{
    while (true) // bijft dit doen, voor altijd
    {
        int distanceFront = getCurrentDistance(TRIG1, ECHO1); // krijg de afstand van de 2 afstand sensors.
        int distanceBack = getCurrentDistance(TRIG2, ECHO2);

        if (distanceFront < 10 || distanceBack < 10) // als de afstand van 1 van de 2 binnen 10 valt laat dan de brug open en dight gaan.
            startBridgeSequence();
    }
}