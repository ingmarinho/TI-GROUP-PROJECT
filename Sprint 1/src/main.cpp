#include "hardware.h"

int testServo(const int position)
{
    float wachttijd = 0.02;

    float positie = round(((10 * wachttijd) + 0.4) / 1000, 7);

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
    // servo(10);
    // servo(90);
}

int main()
{
    setup();
    testHardware();
}