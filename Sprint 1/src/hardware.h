#pragma once

#include <iostream>
#include <wiringPi.h>

#define SERV 6      // GPIO 25 | Physical 22 | Output servo (SERVO)
#define TRIG 10     // GPIO 8  | Physical 24 | Output afstandsensor (TRIG)
#define ECHO 11     // GPIO 7  | Physical 26 | Input afstandsensor (ECHO)

using namespace std;

void setup();
void pulse(const int pin, const float delay1, const float delay2);
int servo(const int position);
int distanceSensor();
