#include "bridge.h"
#include "hardware.h"

static volatile bool sequenceStart = 0;
int counter_open_totaal = 200;
int pointerday = 0;
int counter_week_totaal = 42;
int counter_maand_totaal = 200;
vector<int> counter_dagen_week = {25, 35, 23, 33, 25, 29, 30};
vector<int> counter_afgelopen_dagen = {0, 6, 8, 7, 5, 9, 7, 5, 10, 6, 7, 3, 8, 9, 6, 7, 5, 8, 10, 6, 6, 5, 8, 4, 11, 7, 6, 8, 9, 4};

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

    countersadd();

    if (openBridge() == 0)
        cout << "Bridge has been opened!" << endl;
    
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

    cout << "Totaal is nu: " << counter_open_totaal << ", vandaag is nu: " << counter_afgelopen_dagen[0] << " deze week is nu: " << counter_week_totaal << " deze maand is nu: " << counter_maand_totaal << end1;
    if (pointerday == 0)
        cout << "het is nu maandag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << end1;
    if (pointerday == 1)
        cout << "het is nu dinsdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << end1;
    if (pointerday == 2)
        cout << "het is nu woensdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << end1;
    if (pointerday == 3)
        cout << "het is nu donderdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << end1;
    if (pointerday == 4)
        cout << "het is nu vrijdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << end1;
    if (pointerday == 5)
        cout << "het is nu zaterdag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << end1;
    if (pointerday == 6)
        cout << "het is nu zondag, totaal op maandagen: " << counter_dagen_week[0] << ", totaal op dinsdagen: " << counter_dagen_week[1] << ", totaal op woensdagen: " << counter_dagen_week[2] << ", totaal op donderdagen: " << counter_dagen_week[3] << ", totaal op vrijdagen: " << counter_dagen_week[4] << ", totaal op zaterdagen: " << counter_dagen_week[5] << ", totaal op zondagen: " << counter_dagen_week[6] << end1;
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

void countersadd();
{
    counter_afgelopen_dagen[0]++;
    counter_dagen_week[pointerday]++;
    counter_open_total++;
    counter_week_totaal++;
    counter_maand_totaal++;
}

void countersupdate();
{
    counter_week_totaal = 0;
    counter_maand_totaal = 0;
    for (int i = 29; i > 0; i++)
    {
        counter_afgelopen_dagen[i] = counter_afgelopen_dagen[i-1];
        counter_maand_totaal += counter_afgelopen_dagen[i];
    }
    for (int i = 0; i < 7; i++)
    {
        counter_week_totaal += counter_afgelopen_dagen[i];
    }
    pointerday++;
    if (pointerday == 7)
        pointerday = 0;
}