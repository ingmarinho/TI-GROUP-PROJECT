#include "PracticalSocket.h"
#include <iostream>
#include <thread>
#include <string>
using namespace std;

#define server_ip

//******* CLASS PUBLISHER  ***************************************//
class publisher
{
private:
    SocketAddress remote_addr;
    string topic;
    UDPSocket sock;

public:
    publisher(string topic, string ipadr = "45.63.43.231", int port = 8401) : topic(topic), remote_addr(ipadr.data(), port, SocketAddress::UDP_SOCKET) {}

    void send(string message)
    {
        message = "publish " + topic + " " + message;
        try
        {
            sock.sendTo(message.data(), message.size(), remote_addr);
        }
        catch (SocketException &e)
        {
            cerr << "ERROR sending " << message << " --> " << e.what() << endl;
        }
    }
}; //class publisher

//******** class SUBSCRIPTION *********************************//
class subscription
{

private:
    string topic_string;
    UDPSocket sock;
    void (*call_back)(string);
    SocketAddress remote_addr;

    void wait_for_messages()
    {
        char buffer[128];
        try
        {
            while (true)
            {
                SocketAddress from_adr;
                int n = sock.recvFrom(buffer, 128, from_adr);
                if (n == 0)
                    break;
                buffer[n] = '\0';
                call_back(buffer);
            }
        }
        catch (SocketException &e)
        {
            //socket has closed, jump out of while-loop
        }
    }

public:
    subscription(string s, void (*f)(string), string ipadr = "45.63.43.231", int port = 8401) : topic_string(s), call_back(f),
                                                                                                remote_addr(ipadr.data(), port, SocketAddress::UDP_SOCKET)
    {
        sock.connect(remote_addr);
        subscribe();
        thread t(&subscription::wait_for_messages, this);
        t.detach();
    }

    ~subscription()
    {
        unsubscribe();
        sock.close();
    }

    void subscribe()
    {
        string message = "subscribe " + topic_string + "  ";
        try
        {
            sock.sendTo(message.data(), message.size(), remote_addr);
        }
        catch (SocketException &e)
        {
            cerr << "ERROR subscribing to " << topic_string << " --> " << e.what() << endl;
        }
    }

    void unsubscribe()
    {
        string message = "unsubscribe " + topic_string + "  ";
        try
        {
            sock.sendTo(message.data(), message.size(), remote_addr);
        }
        catch (SocketException &e)
        {
            cerr << "ERROR unsubscribing from " << topic_string << " --> " << e.what() << endl;
        }
    }
}; //class subscription
