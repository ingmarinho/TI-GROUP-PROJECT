#include <wiringPi.h>

int main()
{
    wiringPiSetup();
    pinMode(4, OUTPUT);
    pinMode(5, INPUT);

    while (true)
    {
        if (digitalRead(5) == HIGH)
        {
            digitalWrite(4, HIGH);
        }
        else
        {
            sdigitalWrite(4, LOW);
        }
        delay(100);
    }
}