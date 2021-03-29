#pragma once

#include <iostream>
#include <unistd.h>
#include <wiringPi.h>

#define SERV 6      // GPIO 25 | Physical 22 | Output servo (SERVO)

#define TRIG 10     // GPIO 8  | Physical 24 | Output distance sensor (TRIG)
#define ECHO 11     // GPIO 7  | Physical 26 | Input distance sensor (ECHO)

#define CLCK 31     // GPIO 1  | Physical 28 | Output led strip (CLCK)
#define INFO 26     // GPIO 12 | Physical 32 | Output led strip (INFO)

using namespace std;

void setup();
void pulse(const int pin, const float delay1, const float delay2);
int changeServoPosition(const int position);
int getCurrentDistance();
