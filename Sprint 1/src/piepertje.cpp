#include <iostream>
#include <wiringPi.h>
#include <vector>
#include <unistd.h>

using namespace std;

int BEEP = 24; // GPIO 19

void setup()
{
    wiringPiSetup();
    pinMode(BEEP, OUTPUT);
}

void beep(const int &pin, const unsigned int &delay, const unsigned int &wait_time)
{
    digitalWrite(pin, HIGH);
    usleep(delay);
    digitalWrite(pin, LOW);
    usleep(wait_time);
}

void morse(const int &pin, float &dot_length, const string &text)
{
    dot_length *= 1000000;

    for (unsigned int i = 0; i < text.size(); i++)
    {
        if (text[i] == '.')
        {
            digitalWrite(pin, HIGH);
            usleep(dot_length * 1);
            digitalWrite(pin, LOW);
            usleep(dot_length * 1);
        }
        else if (text[i] == '-')
        {
            digitalWrite(pin, HIGH);
            usleep(dot_length * 3);
            digitalWrite(pin, LOW);
            usleep(dot_length * 1);
        }
        else if (text[i] == ' ')
        {
            usleep(dot_length * 3);
        }
    }
}

int main()
{
    setup();
    morse(BEEP, 0.2f, ".--. -.-- - .... --- -.");
}