#include "boatmaster.h"
#include "bridge.h"

using namespace std;

void bridgeOpenRequest() // Code om inkomende PubSub bericht te controleren en de brug sequence te starten.
{
    string answer = "";
    getline(cin, answer);
    if (answer == "ACCEPT")
    {
        cout << "OPENING BRIDGE!" << endl;
        startBridgeSequence();
    }
    else
        cout << "NEE" << endl;
}

void commandHandler(string message) // Code om te checken of het inkomende bericht vanuit het schip een valide aanvraag is. 
{
    if (message == "OPEN")
    {
        cout << "New request: 'OPEN BRIDGE'" << endl;
        bridgeOpenRequest();
    }
    else
        cout << "Unknown command: " << message << endl;
}

subscription s("boat", commandHandler);



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

// void receiveCommands()
// {
// 	subscription s("boat", commandHandler);
//     string message;

// 	cout << "waiting for messages" << endl;
// 	cout << "type \'s\' to stop"  << endl;
// 	cin.get();
// }
