#include <iostream>
#include <wiringPi.h>

#define SERVO 6
#define TRIG 10
#define ECHO 11

void pulse(const int pin, const float delay1, const float delay2)
{
    digitalWrite(pin, HIGH);
    delay(delay1 * 100);
    digitalWrite(pin, LOW);
    delay(delay2 * 100);
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

int servo(const int position)
{
    float wait_time = 0.02;
    float step_size = 0.002 / 100.0;
    float base_time = 0.0005;
    float servo_pulse_time = base_time + position * step_size;

    pulse(SERVO, servo_pulse_time, wait_time);

    return 0;
}

int sr04()
{
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG, LOW);

    while (digitalRead(ECHO) == LOW);

    long int startTime = micros();
    while (digitalRead(ECHO) == HIGH);
    long int travelTime = micros() - startTime;

    int distance = travelTime / 58;

    return distance;
}

int main()
{
    wiringPiSetup();
    
    pinMode(4, OUTPUT);     // GPIO 23 | Physical 16 | Output knop
    pinMode(5, INPUT);      // GPIO 24 | Physical 8  | Input knop
    pinMode(SERVO, OUTPUT); // GPIO 25 | Physical 22 | Output servo (SERVO)
    pinMode(TRIG, OUTPUT);  // GPIO 8  | Physical 24 | Output afstandsensor (TRIG)
    pinMode(ECHO, INPUT);   // GPIO 7  | Physical 26 | Input afstandsensor (ECHO)

}