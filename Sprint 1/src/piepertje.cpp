#include <iostream>
#include <wiringPi.h>
#include <vector>
#include <unistd.h>

using namespace std;

int BEEP = 19;

void beep(const int &pin, const unsigned int &delay1, const unsigned int &wait_time)
{
    digitalWrite(pin, HIGH);
    usleep(delay1);
    digitalWrite(pin, LOW);
    usleep(wait_time);
}

void morse(const int &pin, int &dot_length, string &text)
{

    for (char &t : text)
    {
        if (t == '.')
        {
            digitalWrite(pin, HIGH);
            usleep(dot_length * 1);
            digitalWrite(pin, LOW);
            usleep(dot_length * 1);
        }
        if (t == '-')
        {
            digitalWrite(pin, HIGH);
            usleep(dot_length * 3);
            digitalWrite(pin, LOW);
            usleep(dot_length * 1);
        }
        if (t == ' ')
        {
            usleep(dot_length * 3);
        }
    }
}

led = 26 GPIO.setup(led, GPIO.OUT)
          morse(18, 0.2, ".--. -.-- - .... --- -.")