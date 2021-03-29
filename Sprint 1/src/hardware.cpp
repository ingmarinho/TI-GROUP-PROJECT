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

    // pinMode(4, OUTPUT);      // GPIO 23 | Physical 16 | Output knop
    // pinMode(5, INPUT);       // GPIO 24 | Physical 8  | Input knop
    pinMode(CLCK, OUTPUT);      // GPIO 1  | Physical 28 | Output led strip (CLCK)
    pinMode(INFO, OUTPUT);      // GPIO 12 | Physical 32 | Output led strip (INFO)
    pinMode(SERV, OUTPUT);      // GPIO 25 | Physical 22 | Output servo (SERVO)
    pinMode(TRIG, OUTPUT);      // GPIO 8  | Physical 24 | Output distance sensor (TRIG)
    pinMode(ECHO, INPUT);       // GPIO 7  | Physical 26 | Input distance sensor (ECHO)
}

void pulse(const int &pin, const unsigned int &delay1, const unsigned int &wait_time)
{
    digitalWrite(pin, HIGH);
    usleep(delay1);
    digitalWrite(pin, LOW);
    usleep(wait_time);
}

int changeServoPosition(const int position)
{
    int wait_time = 20;
    float step_size = 0.02f;
    float base_time = 0.4f;
    unsigned int servo_pulse_time = (base_time + (position * step_size)) * 1000;
    
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
