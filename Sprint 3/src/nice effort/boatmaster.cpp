#include "boatmaster.h"
#include "bridge.h"

using namespace std;

subscription s("boat", commandHandler);
string message;

void bridgeOpenRequest()
{
    string answer;
    getline(cin, answer);
    if (answer == "ACCEPT")
    {
        cout << "OPENING BRIDGE!" << endl;
        startBridgeSequence();
    }
    else
        sendCommand(p, "Opening bridge currently unavailable, please try again later");
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

// void sendCommands()
// {
//     while (true)
//     {
//         cout << "$ ";
//         getline(cin, message);
//         if (message == "STOP")
//             break;
//     }
// }