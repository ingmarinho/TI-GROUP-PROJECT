#include "pubsub.h"
#include <iostream>

int main()
{
	publisher p("boat");

	string message;
	cout << "Verstuur commandos naar de brugwachter:" << endl;
	while(true)
    {
		cout << "$ ";
		getline(cin, message);
		if (message == "stop") break;

		p.send(message);
	}
}