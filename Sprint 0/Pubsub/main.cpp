#include <iostream>
#include <wiringPi.h>
#include "pubsub.h"

using namespace std;

string getPublisher()
{
    return "ingmar";
}

string getSubscription()
{
    return "kenny";
}

void sendCommand(publisher &p, string message)
{
    p.send(message);
}

void commandHandler(string message)
{
    if (message == "ON")
    {
        cout << "Command received: " << message << endl;
        digitalWrite(0, HIGH);
    }
    else if (message == "OFF")
    {
        cout << "Command received: " << message << endl;
        digitalWrite(0, LOW);
    }
    else
        cout << "Message received: " << message << endl;
}

int main()
{
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(5, INPUT);

    publisher p(getPublisher());
    subscription s(getSubscription(), commandHandler);
    string message;

    while(true)
    {
		cout << "$ ";
        getline(cin, message);
		if (message == "stop") break;
		// sendCommand(p, message);
	}

}