#include "hardware.h"

using namespace std;

void setup()
{
    wiringPiSetup();

    pinMode(TRIG1, OUTPUT); // GPIO 15 | Output distance sensor (TRIG1) (BOAT DETECTION FRONT)
    pinMode(ECHO1, INPUT);  // GPIO 14 | Input distance sensor (ECHO1) (BOAT DETECTION FRONT)
    pinMode(TRIG2, OUTPUT); // GPIO 18 | Output distance sensor (TRIG2) (BOAT DETECTION BACK)
    pinMode(ECHO2, INPUT);  // GPIO 23 | Input distance sensor (ECHO2) (BOAT DETECTION BACK)

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);

    pinMode(SERV1, OUTPUT); // GPIO 25 | Output servo (SERV1) (BRIDGE)
    pinMode(SERV2, OUTPUT); // GPIO 26 | Output servo (SERV2) (BARRIER 1)
    pinMode(SERV3, OUTPUT); // GPIO 12 | Output servo (SERV3) (SERV3) (BARRIER 2)

    pinMode(CLCK, OUTPUT); // GPIO 1  | Output led strip (CLCK) (BRIDGE LIGHTS)
    pinMode(INFO, OUTPUT); // GPIO 12 | Output led strip (INFO) (BRIDGE LIGHTS)

    pinMode(BEEP, OUTPUT);
}

void pulse(const int &pin, const unsigned int &delay1, const unsigned int &wait_time) // code om voor een bepaalde tijd een led aan te doen
{
    digitalWrite(pin, HIGH);
    usleep(delay1);
    digitalWrite(pin, LOW);
    usleep(wait_time);
}

void changeServoPosition(const int pin, const int position) // 0 to 100 (0 to 180°)
{
    int wait_time = 20; // basis reken waardes voor de formule
    float step_size = 0.02f;
    float base_time = 0.4f;
    unsigned int servo_pulse_time = (base_time + (position * step_size)) * 1000; // conversion to microseconds (usleep is in microseconds)

    pulse(pin, servo_pulse_time, wait_time); // stuur een servo aan op pin.
}

void activateLeds() // activeer 2 leds om aan te gaan, voor het waarschuw singaal.
{
    digitalWrite(LED1, 1);
    digitalWrite(LED2, 1);
    delay(500);
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0);
}

void send_bytes(std::vector<bool> bytes) // een rij van 4 boolians die in de ledstrip bepalen welke kleur de volgende lamp heeft.
{
    vector<bool> k = {};

    for (unsigned int i = 0; i < bytes.size(); i++) // loop door de 4 gegeven waardes heen.
    {
        if (i == 0 && bytes[i]) // zorg er voor dat de leds niet te fel zijn als die aan moet.
        {
            k = {1, 1, 1, 0, 0, 0, 1, 0};
        }
        else if (i != 0 && bytes[i]) // zorg er voor dat een RGB kleur volledig word laten zien.
        {
            k = {1, 1, 1, 1, 1, 1, 1, 1};
        }
        else // stuur anders niks door
        {
            k = {0, 0, 0, 0, 0, 0, 0, 0};
        }

        for (unsigned int j = 0; j < k.size(); j++) // stuur bits ob basis van de hierboven gegeven waardes door.
        {
            if (k[j]) // stuur een 1 of een 0
                digitalWrite(INFO, HIGH);
            else
                digitalWrite(INFO, LOW);
            digitalWrite(CLCK, HIGH);
            digitalWrite(CLCK, LOW);
        }
    }
}

void activateBoatTrafficLight(bool color) // 0 = rood | 1 = groen // zeg welke kleur de ledstrip moet hebben.
{

    send_bytes({0, 0, 0, 0}); // reset de ledstrip
    for (unsigned int i = 0; i < 9; i++) // stuur informatie ter waarde van negen leds door, anders heeft de laaste led problemen.
    {
        if (!color)
            send_bytes({1, 0, 0, 1}); // maak de led rood
        else
            send_bytes({1, 0, 1, 0}); // maak de led groen
    }
}

void barrierSound() // maak een geluid voor de slagbomen.
{
    digitalWrite(BEEP, HIGH);
    delay(200);
    digitalWrite(BEEP, LOW);
}

int getCurrentDistance(const int trig_pin, const int echo_pin) // bepaal de afstand van een afstand sensor.
{
    digitalWrite(trig_pin, HIGH); // laat de sensor beginnen met meten.
    delay(20);
    digitalWrite(trig_pin, LOW);

    while (digitalRead(echo_pin) == LOW); // wacht tot dat de echo een hoge output heeft.
    long int startTime = micros(); // meet de tijd
    while (digitalRead(echo_pin) == HIGH); // wacht tot dat de echo een lage output heeft.

    long int travelTime = micros() - startTime; // bereken de tijd tussen het begin van de hoge output en het einde.

    int distance = travelTime / 58; // bereken de afstand in hele centimeters

    return distance; // geef de afstand terug.
}
