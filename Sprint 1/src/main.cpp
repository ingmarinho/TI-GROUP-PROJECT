#include <iostream>
#include <wiringPi.h>

void pulse(const int pin, const float delay1, const float delay2)
{
    digitalWrite(pin, HIGH);
    delay(delay1 * 100)
    digitalWrite(pin, LOW);
    delay(delay2 * 100)
}

void knop()
{
    while (true)
    {
        if (digitalRead(5) == HIGH)
        {
            digitalWrite(4, HIGH);
        }
        else
        {
            digitalWrite(4, LOW);
        }
        delay(100);
    }
}

void servo()
{
    float wait_time = 0.02;
    float step_size = 0.002 / 100.0;
    float base_time = 0.0005;
    float servo_pulse_time = base_time + i * step_size;

    pulse(6, servo_pulse_time, wait_time);

    return 0;
}

int main()
{
    wiringPiSetup();
    pinMode(4, OUTPUT);     // GPIO 23 | Physical 16
    pinMode(5, INPUT);      // GPIO 24 | Physical 8

}