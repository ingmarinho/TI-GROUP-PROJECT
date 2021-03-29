#pragma once

#include <iostream>
#include <wiringPi.h>

#define SERVO 6
#define TRIG 10
#define ECHO 11

using namespace std;

wiringPiSetup();

// pinMode(4, OUTPUT);     // GPIO 23 | Physical 16 | Output knop
// pinMode(5, INPUT);      // GPIO 24 | Physical 8  | Input knop
pinMode(SERVO, OUTPUT); // GPIO 25 | Physical 22 | Output servo (SERVO)
pinMode(TRIG, OUTPUT);  // GPIO 8  | Physical 24 | Output afstandsensor (TRIG)
pinMode(ECHO, INPUT);   // GPIO 7  | Physical 26 | Input afstandsensor (ECHO)

void pulse(const int pin, const float delay1, const float delay2);
int servo(const int position);
int afstandSensor();