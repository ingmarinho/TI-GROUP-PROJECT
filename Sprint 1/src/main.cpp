#include "hardware.h"

int testServo(const int position)
{
    float wachttijd = 200;

    float positie = round(((10000 * wachttijd) + 400) / 1000000, 7000);

    pulse(positie, wachttijd - positie);

    return 0;
}

void testHardware()
{
    int x = 0;
    while (x < 20)
    {
        int distance = distanceSensor();
        cout << "Distance in cm: " << distance << endl;
        delay(500);
        x++;
    }

    testServo(10);
    testServo(90);
}

int main()
{
    setup();
    testHardware();
}