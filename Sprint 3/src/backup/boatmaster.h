#pragma once

#include <iostream>
#include <string>
#include "pubsub.h"
#include "bridge.h"

void bridgeOpenRequest();
void commandHandler(string message);
void receiveCommands();