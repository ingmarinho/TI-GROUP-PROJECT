//voorbeeld1.cpp
//voorbeeld programma voor een publisher
//builden met g++ -o <naam van executable> voorbeeld1.cpp PracticalSocket.cpp

#include "pubsub.h"
#include <iostream>


int main()
{

	//maak een publisher voor een topic
	//parameter 1: naam van de topic (mag geen spaties bevatten)
	publisher p("boat");

	string s;
	cout << "voer berichten in om te verzenden" << endl;
	cout << "\"stop\" om te stoppen" << endl;
	while(true)
    {
		cout << "? ";
		getline(cin, s);
		if (s == "stop") break;

		p.send(s);
	}
}