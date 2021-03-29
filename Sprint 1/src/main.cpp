#include "hardware.h"


int testServo()
{
    float wait_time = 0.02;
    float step_size = 0.002 / 100.0;
    float base_time = 0.0005;
    float servo_pulse_time;
    for (int i = 0; i < 101; i++)
    {
        servo_pulse_time = base_time + i * step_size;
        pulse(6, servo_pulse_time, wait_time);
    }

    for (int i = 100; i < 0; i--)
    {
        servo_pulse_time = base_time + i * step_size;
        pulse(6, servo_pulse_time, wait_time);
    }
    pulse(SERV, servo_pulse_time, wait_time);

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
}


int main()
{
    setup();
    testHardware();

}