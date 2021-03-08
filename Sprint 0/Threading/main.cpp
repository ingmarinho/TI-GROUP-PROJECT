#include <wiringPi.h>
#include <iostream>

void pulse(int pin, float delay1, float delay2)
{
    digitalWrite(pin, HIGH);
    delay(delay1 * 100)
    digitalWrite(pin, LOW);
    delay(delay2 * 100)
}

PI_THREAD(servo)
{
    float wait_time = 0.02;
    float step_size = 0.002 / 100.0;
    float base_time = 0.0005;

    float servo_pulse_time;
    for (int i = 0; i < 101; i++)
    {
        servo_pulse_time = base_time + i * step_size;
        pulse(6, servo_pulse_time, wait_time);
    }

    for (int i = 100; i < 0; i--)
    {
        servo_pulse_time = base_time + i * step_size;
        pulse(6, servo_pulse_time, wait_time);
    }

    return 0;
}


int main()
{
    wiringPiSetup();
    pinMode(6, OUTPUT);
    pinMode(27, INPUT);
    

    while (true)
    {
        srand(time(0));
        if (digitalRead(27) == HIGH)
        {
            std::cout << "Position changed" << std::endl;
            int t = piThreadCreate(servo);
            if (t != 0)
                std::cout << "thread didn't run correctly" << std::endl;
        }
        delay(150);
    }
}