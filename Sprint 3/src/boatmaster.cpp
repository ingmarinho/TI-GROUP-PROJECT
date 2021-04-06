#include "boatmaster.h"
#include "bridge.h"

void sendCommand(publisher &p, string message)
{
    p.send(message);
}

void bridgeOpenRequest()
{
    string answer;
    getline(cin, answer);
    if (answer == "ACCEPT")
        startBridgeSequenced();
    else
        sendCommand("Opening bridge currently unavailable, please try again later");
}

void commandHandler(string message)
{
    if (message == "OPEN")
    {
        cout << "New request: 'OPEN BRIDGE'" << endl;
        bridgeOpenRequest();
    }
    else
        cout << "Unknown command: " << message << endl;
}

int sendCommands()
{
    while (true)
    {
        cout << "$ ";
        getline(cin, message);
        if (message == "STOP")
            break;
    }
}