#pragma once

#include <iostream>
#include <unistd.h>
#include <wiringPi.h>


#define TRIG1 16    // GPIO 15  | Physical  | Output distance sensor (TRIG1) (BOAT DETECTION FRONT)
#define ECHO1 15    // GPIO 14  | Physical  | Input distance sensor (ECHO1) (BOAT DETECTION FRONT)
#define TRIG2 1     // (TRIG2) (BOAT DETECTION BACK)
#define ECHO2 4     // (ECHO2) (BOAT DETECTION BACK)

#define SERV1 5     // GPIO 25 | Physical 22 | Output servo (SERV1) (BRIDGE)
#define SERV2 31    // GPIO 26 | Physical 37 | Output servo (SERV2) (BARRIER 1)
#define SERV3 0     // (SERV3) (BARRIER 2)

#define CLCK 10     // GPIO 8  | Physical 28 | Output led strip (CLCK) (TRAFFIC LIGHTS)
#define INFO 6     // GPIO 25 | Physical 32 | Output led strip (INFO) (TRAFFIC LIGHTS)

#define BEEP 
using namespace std;

void setup();
void pulse(const int pin, const float delay1, const float delay2);
int changeServoPositionBridge(const int position)
int getCurrentDistanceFront();
int getCurrentDistanceBack();
