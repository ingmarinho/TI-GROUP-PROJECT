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
    pinMode(TRIG1, OUTPUT);      // GPIO 8  | Physical 24 | Output distance sensor (TRIG1) (BOAT DETECTION FRONT)
    pinMode(ECHO1, INPUT);       // GPIO 7  | Physical 26 | Input distance sensor (ECHO1) (BOAT DETECTION FRONT)
    pinMode(TRIG2, OUTPUT);      // (TRIG2) (BOAT DETECTION BACK)
    pinMode(ECHO2, INPUT);       // (ECHO2) (BOAT DETECTION BACK)

    pinMode(SERV1, OUTPUT);     // GPIO 25 | Physical 22 | Output servo (SERV1) (BRIDGE)
    pinMode(SERV2, OUTPUT);     // GPIO 26 | Physical 37 | Output servo (SERV2) (BARRIER 1)
    pinMode(SERV3, OUTPUT);     // (SERV3) (BARRIER 2)

    pinMode(CLCK, OUTPUT);      // GPIO 1  | Physical 28 | Output led strip (CLCK) (TRAFFIC LIGHTS)
    pinMode(INFO, OUTPUT);      // GPIO 12 | Physical 32 | Output led strip (INFO) (TRAFFIC LIGHTS)
}

void pulse(const int &pin, const unsigned int &delay1, const unsigned int &wait_time)
{
    digitalWrite(pin, HIGH);
    usleep(delay1);
    digitalWrite(pin, LOW);
    usleep(wait_time);
}

int changeServoPosition(const int position) // 0 to 100 (0 to 180°)
{
    int wait_time = 20;
    float step_size = 0.02f;
    float base_time = 0.4f;
    unsigned int servo_pulse_time = (base_time + (position * step_size)) * 1000; // conversion to microseconds (usleep is in microseconds)
    
    pulse(SERV1, servo_pulse_time, wait_time);

    return 0;
}

int getCurrentDistanceFront()
{
    digitalWrite(TRIG1, HIGH);
    delay(20);
    digitalWrite(TRIG1, LOW);

    while (digitalRead(ECHO1) == LOW);
    long int startTime = micros();
    while (digitalRead(ECHO1) == HIGH);

    long int travelTime = micros() - startTime;

    int distance = travelTime / 58;

    return distance;
}

int getCurrentDistanceBack()
{
    digitalWrite(TRIG2, HIGH);
    delay(20);
    digitalWrite(TRIG2, LOW);

    while (digitalRead(ECHO2) == LOW);
    long int startTime = micros();
    while (digitalRead(ECHO2) == HIGH);

    long int travelTime = micros() - startTime;

    int distance = travelTime / 58;

    return distance;
}

