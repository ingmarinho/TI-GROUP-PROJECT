#pragma once

#include <iostream>
#include <string>
#include "pubsub.h"
#include "bridge.h"

using namespace std;

void sendCommand(publisher &p, string message);
void bridgeOpenRequest();
void commandHandler(string message);

publisher p("controlcentre");
subscription s("boat", commandHandler);
string message;

void sendCommands();