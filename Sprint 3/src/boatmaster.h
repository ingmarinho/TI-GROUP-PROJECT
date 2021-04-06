#pragma once

#include <iostream>
#include "pubsub.h"

using namespace std;

void sendCommand(publisher &p, string message);
void bridgeOpenRequest();
void commandHandler(string message);

publisher p("controlcentre");
subscription s("boat", commandHandler);
string message;

int sendCommands();