#pragma once

#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <vector>


#define TRIG1 16    // GPIO 15 | Output distance sensor (TRIG1) (BOAT DETECTION FRONT)
#define ECHO1 15    // GPIO 14 | Input distance sensor (ECHO1) (BOAT DETECTION FRONT)
#define TRIG2 1     // GPIO 18 | Output distance sensor (TRIG2) (BOAT DETECTION BACK)
#define ECHO2 4     // GPIO 23 | Input distance sensor (ECHO2) (BOAT DETECTION BACK)

#define LED1 11
#define LED2 27

#define SERV1 5     // GPIO 25 | Output servo (SERV1) (BRIDGE)
#define SERV2 31    // GPIO 26 | Output servo (SERV2) (BARRIER 1)
#define SERV3 26    // GPIO 12 | Output servo (SERV3) (BARRIER 2)

#define CLCK 10     // GPIO 8 | Output led strip (CLCK) (BRIDGE LIGHT)
#define INFO 6     // GPIO 25 | Output led strip (INFO) (BRIDGE LIGHT)

#define BEEP 
using namespace std;

void setup();
void pulse(const int pin, const float delay1, const float delay2);
int changeServoPosition(const int pin, const int position);
int getCurrentDistance(const int trig_pin, const int echo_pin);
int activateLeds();
int activateBoatTrafficLight(bool color);
void send_bytes(vector<bool> bytes);
