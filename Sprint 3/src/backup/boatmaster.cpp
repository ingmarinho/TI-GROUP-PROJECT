#include "boatmaster.h"
#include "bridge.h"

using namespace std;

void bridgeOpenRequest()                                // Code om als brugwachter te bepalen of de brug wel of niet open kan naar aanleiding van een verzoek (van een schipper).
{
    string answer = "";
    getline(cin, answer);
    if (answer == "accept")
    {
        cout << "'OPEN BRIDGE' request has been accepted." << endl;
        startBridgeSequence();
    }
    else
        cout << "'OPEN BRIDGE' request has been denied." << endl;
}

void commandHandler(string message)                     // Code om te checken of het inkomende bericht vanuit het schip een valide aanvraag is. 
{
    if (message == "open")
    {
        cout << "New request: 'OPEN BRIDGE'" << endl;
        bridgeOpenRequest();
    }
    else
        cout << "Unknown command: " << message << endl;
}

subscription s("boat", commandHandler);