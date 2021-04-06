#include "bridge.h"
#include "hardware.h"

static volatile bool sequenceStart = 0;
int counter_open_total = 200;
int pointerday = 0;
int counter_week_total = 42;
int counter_month_total = 200;
vector<int> counter_days_per_week = {25, 30, 29, 25, 33, 23, 35};
vector<int> counter_past_days = {0, 6, 8, 7, 5, 9, 7, 5, 10, 6, 7, 3, 8, 9, 6, 7, 5, 8, 10, 6, 6, 5, 8, 4, 11, 7, 6, 8, 9, 4};

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
        cout << "Bridge has been closed!" << "\n";

    delay(1000);

    playBarrierSound();

    if (closeBarriers() == 0)
        cout << "Barriers are opening!" << "\n";

    cout << "Totaal aantal keren geopend: " << counter_open_total << "\n"
    << "Aantal keer geopend vandaag: " << counter_past_days[0] << "\n"
    << "Aantal keer geopend deze week: "<< counter_week_total << "\n"
    << "Aantal keer geopend deze maand: " << counter_month_total << "\n";


    if (pointerday == 0)
        cout << "het is nu maandag, totaal op maandagen: " << counter_days_per_week[0] << ", totaal op dinsdagen: " << counter_days_per_week[1] << ", totaal op woensdagen: " << counter_days_per_week[2] << ", totaal op donderdagen: " << counter_days_per_week[3] << ", totaal op vrijdagen: " << counter_days_per_week[4] << ", totaal op zaterdagen: " << counter_days_per_week[5] << ", totaal op zondagen: " << counter_days_per_week[6] << endl;
    if (pointerday == 1)
        cout << "het is nu dinsdag, totaal op maandagen: " << counter_days_per_week[0] << ", totaal op dinsdagen: " << counter_days_per_week[1] << ", totaal op woensdagen: " << counter_days_per_week[2] << ", totaal op donderdagen: " << counter_days_per_week[3] << ", totaal op vrijdagen: " << counter_days_per_week[4] << ", totaal op zaterdagen: " << counter_days_per_week[5] << ", totaal op zondagen: " << counter_days_per_week[6] << endl;
    if (pointerday == 2)
        cout << "het is nu woensdag, totaal op maandagen: " << counter_days_per_week[0] << ", totaal op dinsdagen: " << counter_days_per_week[1] << ", totaal op woensdagen: " << counter_days_per_week[2] << ", totaal op donderdagen: " << counter_days_per_week[3] << ", totaal op vrijdagen: " << counter_days_per_week[4] << ", totaal op zaterdagen: " << counter_days_per_week[5] << ", totaal op zondagen: " << counter_days_per_week[6] << endl;
    if (pointerday == 3)
        cout << "het is nu donderdag, totaal op maandagen: " << counter_days_per_week[0] << ", totaal op dinsdagen: " << counter_days_per_week[1] << ", totaal op woensdagen: " << counter_days_per_week[2] << ", totaal op donderdagen: " << counter_days_per_week[3] << ", totaal op vrijdagen: " << counter_days_per_week[4] << ", totaal op zaterdagen: " << counter_days_per_week[5] << ", totaal op zondagen: " << counter_days_per_week[6] << endl;
    if (pointerday == 4)
        cout << "het is nu vrijdag, totaal op maandagen: " << counter_days_per_week[0] << ", totaal op dinsdagen: " << counter_days_per_week[1] << ", totaal op woensdagen: " << counter_days_per_week[2] << ", totaal op donderdagen: " << counter_days_per_week[3] << ", totaal op vrijdagen: " << counter_days_per_week[4] << ", totaal op zaterdagen: " << counter_days_per_week[5] << ", totaal op zondagen: " << counter_days_per_week[6] << endl;
    if (pointerday == 5)
        cout << "het is nu zaterdag, totaal op maandagen: " << counter_days_per_week[0] << ", totaal op dinsdagen: " << counter_days_per_week[1] << ", totaal op woensdagen: " << counter_days_per_week[2] << ", totaal op donderdagen: " << counter_days_per_week[3] << ", totaal op vrijdagen: " << counter_days_per_week[4] << ", totaal op zaterdagen: " << counter_days_per_week[5] << ", totaal op zondagen: " << counter_days_per_week[6] << endl;
    if (pointerday == 6)
        cout << "het is nu zondag, totaal op maandagen: " << counter_days_per_week[0] << ", totaal op dinsdagen: " << counter_days_per_week[1] << ", totaal op woensdagen: " << counter_days_per_week[2] << ", totaal op donderdagen: " << counter_days_per_week[3] << ", totaal op vrijdagen: " << counter_days_per_week[4] << ", totaal op zaterdagen: " << counter_days_per_week[5] << ", totaal op zondagen: " << counter_days_per_week[6] << endl;
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

void countersadd()
{
    counter_past_days[0]++;
    counter_days_per_week[pointerday]++;
    counter_open_total++;
    counter_week_total++;
    counter_month_total++;
}

void countersupdate()
{
    counter_week_total = 0;
    counter_month_total = 0;
    for (int i = 29; i > 0; i++)
    {
        counter_past_days[i] = counter_past_days[i-1];
        counter_month_total += counter_past_days[i];
    }
    for (int i = 0; i < 7; i++)
    {
        counter_week_total += counter_past_days[i];
    }
    pointerday++;
    if (pointerday == 7)
        pointerday = 0;
}