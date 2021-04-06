#include "PracticalSocket.h"
#include <iostream>
#include <thread>
#include <string>
using namespace std;



//******* CLASS PUBLISHER  ***************************************//
class publisher{
private:
	//string topic;
	TCPSocket sock;
	
	
public:
	publisher(string topic, string ipadr = "45.63.43.231", int port = 8402) { 
		try{
			SocketAddress foreignaddr(ipadr.data(), port, SocketAddress::TCP_SOCKET);
			sock.connect(foreignaddr);
			string firstmessage = "publisher " + topic + " ";
			sock.send(firstmessage.data(), firstmessage.size());
		}
		catch(SocketException& e) {
			cerr << "ERROR creating publisher to " << topic << " --> " << e.what() << endl;
		}
	}
	
	~publisher(){
		sock.close();
	}
	
	void send(string message){
	
		try{
			int len = message.size();
			if(len > 99) {
				len = 99;
				message = message.substr(0, len);
			}
			if(len == 0)
				return;
			char ch1 = len / 10 + 48;
			char ch2 = len % 10 + 48;
			char buffer[2] = {ch1, ch2};
			sock.send(buffer, 2);
			sock.send(message.data(), message.size());
		}
		catch(SocketException& e) {
			cerr << "ERROR sending " << message << " --> " << e.what() << endl;
		}
	}
}; //class publisher



//******** class SUBSCRIPTION *********************************//
class subscription{
	
private:
	string topic;
	TCPSocket sock;
	void (*call_back)(string);
	SocketAddress remote_addr;
			
	void wait_for_messages(){
		char lenbuffer [2];
		char buffer [101];
		while(true) {
			int n = sock.recvFully(lenbuffer, 2);
       		if (n == 0) break;
       		int len = (lenbuffer[0]-48)*10 + lenbuffer[1]-48;
       		n = sock.recvFully(buffer, len);
       		if (n == 0) break;
	   		buffer[len] = '\0';
	   		call_back(buffer);
		}
		
	}
	
public:
	subscription(string s, void (*f)(string), string ipadr = "45.63.43.231", int port = 8402):
	topic (s),  call_back(f), 
	remote_addr(ipadr.data(), port, SocketAddress::TCP_SOCKET) {
		try{
			sock.connect(remote_addr);
			subscribe();	
			thread t(&subscription::wait_for_messages, this);
			t.detach();
		}
		catch(SocketException& e) {
			cerr << "ERROR: cannot create subcription to " << topic << " --> " << e.what() << endl;

		}
	}
	
	~subscription(){ 		
		sock.close();		 
	}
	
	void subscribe(){
		string message = "subscription " + topic + "  ";
		sock.send(message.data(), message.size());
	}
			
	
		
};  //class subscription
		
