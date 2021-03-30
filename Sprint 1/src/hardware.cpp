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

    // pinMode(4, OUTPUT);      // GPIO 23 | Output knop
    // pinMode(5, INPUT);       // GPIO 24 | Input knop
    pinMode(TRIG1, OUTPUT);     // GPIO 15 | Output distance sensor (TRIG1) (BOAT DETECTION FRONT)
    pinMode(ECHO1, INPUT);      // GPIO 14 | Input distance sensor (ECHO1) (BOAT DETECTION FRONT)
    pinMode(TRIG2, OUTPUT);     // GPIO 18 | Output distance sensor (TRIG2) (BOAT DETECTION BACK)
    pinMode(ECHO2, INPUT);      // GPIO 23 | Input distance sensor (ECHO2) (BOAT DETECTION BACK)

    pinMode(SERV1, OUTPUT);     // GPIO 25 | Output servo (SERV1) (BRIDGE)
    pinMode(SERV2, OUTPUT);     // GPIO 26 | Output servo (SERV2) (BARRIER 1)
    pinMode(SERV3, OUTPUT);     // GPIO 12 | Output servo (SERV3) (SERV3) (BARRIER 2)

    pinMode(CLCK, OUTPUT);      // GPIO 1  | Output led strip (CLCK) (BRIDGE LIGHTS)
    pinMode(INFO, OUTPUT);      // GPIO 12 | Output led strip (INFO) (BRIDGE LIGHTS)
}

void pulse(const int &pin, const unsigned int &delay1, const unsigned int &wait_time)
{
    digitalWrite(pin, HIGH);
    usleep(delay1);
    digitalWrite(pin, LOW);
    usleep(wait_time);
}

int changeServoPosition(const int pin, const int position) // 0 to 100 (0 to 180°)
{
    int wait_time = 20;
    float step_size = 0.02f;
    float base_time = 0.4f;
    unsigned int servo_pulse_time = (base_time + (position * step_size)) * 1000; // conversion to microseconds (usleep is in microseconds)
    
    pulse(pin, servo_pulse_time, wait_time);

    return 0;
}

int getCurrentDistance(const int trig_pin, const int echo_pin)
{
    digitalWrite(trig_pin, HIGH);
    delay(20);
    digitalWrite(trig_pin, LOW);

    while (digitalRead(echo_pin) == LOW);
    long int startTime = micros();
    while (digitalRead(echo_pin) == HIGH);

    long int travelTime = micros() - startTime;

    int distance = travelTime / 58;

    return distance;
}

