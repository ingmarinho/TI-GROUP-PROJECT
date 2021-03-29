#pragma once

#include <iostream>
#include <wiringPi.h>

#define SERVO 6
#define TRIG 10
#define ECHO 11

using namespace std;

void setup();
void pulse(const int pin, const float delay1, const float delay2);
int servo(const int position);
int distanceSensor();
