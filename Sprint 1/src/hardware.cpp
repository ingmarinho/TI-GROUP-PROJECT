#include "hardware.h"

// void knop()
// {
//     while (true)
//     {
//         if (digitalRead(5) == HIGH)
//         {
//             digitalWrite(4, HIGH);
//         }
//         else
//         {
//             digitalWrite(4, LOW);
//         }
//         delay(100);
//     }
// }

void setup()
{
    wiringPiSetup();

    // pinMode(4, OUTPUT);     // GPIO 23 | Physical 16 | Output knop
    // pinMode(5, INPUT);      // GPIO 24 | Physical 8  | Input knop
    // pinMode(SERV, OUTPUT); // GPIO 25 | Physical 22 | Output servo (SERVO)
    softServoSetup(SERV);
    pinMode(TRIG, OUTPUT);  // GPIO 8  | Physical 24 | Output distance sensor (TRIG)
    pinMode(ECHO, INPUT);   // GPIO 7  | Physical 26 | Input distance sensor (ECHO)
}

void pulse(const int pin, const float delay1, const float delay2)
{
    digitalWrite(pin, HIGH);
    delay(delay1 * 1000);
    digitalWrite(pin, LOW);
    delay(delay2 * 1000);
}

int changeServoPosition(const int position)
{
    float wait_time = 0.02;
    float step_size = 0.002 / 100.0;
    float base_time = 0.0005;
    float servo_pulse_time = base_time + position * step_size;

    pulse(SERV, servo_pulse_time, wait_time);

    return 0;
}

int getCurrentDistance()
{
    digitalWrite(TRIG, HIGH);
    delay(20);
    digitalWrite(TRIG, LOW);

    while (digitalRead(ECHO) == LOW);

    long int startTime = micros();
    while (digitalRead(ECHO) == HIGH);
    long int travelTime = micros() - startTime;

    int distance = travelTime / 58;

    return distance;
}
