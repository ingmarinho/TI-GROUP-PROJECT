#include "hardware.h"

using namespace std;

void setup()                                                                                    // Alle pins worden geconfigureerd.
{
    wiringPiSetup();

    pinMode(TRIG1, OUTPUT);                                                                     // GPIO 15 | Output distance sensor (TRIG1) (BOAT DETECTION FRONT)
    pinMode(ECHO1, INPUT);                                                                      // GPIO 14 | Input distance sensor (ECHO1) (BOAT DETECTION FRONT)
    pinMode(TRIG2, OUTPUT);                                                                     // GPIO 18 | Output distance sensor (TRIG2) (BOAT DETECTION BACK)
    pinMode(ECHO2, INPUT);                                                                      // GPIO 23 | Input distance sensor (ECHO2) (BOAT DETECTION BACK)

    pinMode(LED1, OUTPUT);                                                                      // GPIO 7  | Output waarschuwings LED links  (LED1)
    pinMode(LED2, OUTPUT);                                                                      // GPIO 16 | Output waarschuwings LED rechts (LED2)

    pinMode(SERV1, OUTPUT);                                                                     // GPIO 24 | Output servo (SERV1) (BRIDGE)
    pinMode(SERV2, OUTPUT);                                                                     // GPIO 1  | Output servo (SERV2) (BARRIER 1)
    pinMode(SERV3, OUTPUT);                                                                     // GPIO 12 | Output servo (SERV3) (BARRIER 2)

    pinMode(CLCK, OUTPUT);                                                                      // GPIO 8  | Output led strip (CLCK) (BRIDGE LIGHT)
    pinMode(INFO, OUTPUT);                                                                      // GPIO 25 | Output led strip (INFO) (BRIDGE LIGHT)

    pinMode(BEEP, OUTPUT);                                                                      // GPIO 21 | Output piepertje (GELUID)
}

void pulse(const int &pin, const unsigned int &delay1, const unsigned int &wait_time)           // Code om voor een pulse te geven aan de hardware.
{
    digitalWrite(pin, HIGH);
    usleep(delay1);
    digitalWrite(pin, LOW);
    usleep(wait_time);
}

void changeServoPosition(const int pin, const int position)                                     // Servo positie van 0 tot 100 (0 tot 180°).
{
    int wait_time = 20;                                                                         // Basis waardes voor de rekenformule van de servo. 
    float step_size = 0.02f;
    float base_time = 0.4f;
    unsigned int servo_pulse_time = (base_time + (position * step_size)) * 1000;                // Formule voor servo pulse time (*1000 omdat usleep in microseconden is).

    pulse(pin, servo_pulse_time, wait_time);                                                    // Geef de pulse met de juiste waardes aan de servo..
}

void activateLeds()                                                                             // Activeer 2 leds om aan te gaan, voor het waarschuwings signaal.
{
    digitalWrite(LED1, 1);
    digitalWrite(LED2, 1);
    delay(500);
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0);
}

void send_bytes(std::vector<bool> bytes)                                                        // Een vector van 4 booleans die in de ledstrip bepalen welke kleur de LEDs krijgen.
{
    vector<bool> k = {};

    for (unsigned int i = 0; i < bytes.size(); i++)                                             // Loop door de vier gegeven waardes heen.
    {
        if (i == 0 && bytes[i])                                                                 // Zorg er voor dat de leds niet te fel zijn als ze aan staan.
        {
            k = {1, 1, 1, 0, 0, 0, 1, 0};
        }
        else if (i != 0 && bytes[i])                                                            // Zorg er voor dat een RGB kleur volledig wordt laten zien.
        {
            k = {1, 1, 1, 1, 1, 1, 1, 1};
        }
        else                                                                                    // Stuur anders niks door.
        {
            k = {0, 0, 0, 0, 0, 0, 0, 0};
        }

        for (unsigned int j = 0; j < k.size(); j++)                                             // Stuur bits op basis van de hierboven gegeven waardes door.
        {
            if (k[j])                                                                           // Stuur een 1 of een 0.
                digitalWrite(INFO, HIGH);
            else
                digitalWrite(INFO, LOW);
            digitalWrite(CLCK, HIGH);
            digitalWrite(CLCK, LOW);
        }
    }
}

void activateBoatTrafficLight(bool color)                                                       // 0 = rood | 1 = groen // Zeg welke kleur de ledstrip moet hebben.
{

    send_bytes({0, 0, 0, 0});                                                                   // Reset de ledstrip
    for (unsigned int i = 0; i < 9; i++)                                                        // Stuur informatie ter waarde van negen leds door, anders heeft de laaste led problemen.
    {
        if (!color)
            send_bytes({1, 0, 0, 1});                                                           // Maak de LEDs rood.
        else
            send_bytes({1, 0, 1, 0});                                                           // Maak de LEDs groen.
    }
}

// void barrierSound() // Geluid voor de slagbomen.
// {
//     digitalWrite(BEEP, HIGH);
//     delay(200);
//     digitalWrite(BEEP, LOW);
// }

int getCurrentDistance(const int trig_pin, const int echo_pin)                                  // Functionaliteit van de afstandssensoren.
{
    digitalWrite(trig_pin, HIGH);                                                               // Laat de sensor beginnen met meten.
    delay(20);
    digitalWrite(trig_pin, LOW);

    while (digitalRead(echo_pin) == LOW);                                                       // Wacht tot dat de echo een hoge output heeft.
    long int startTime = micros();                                                              // Meet de tijd.
    while (digitalRead(echo_pin) == HIGH);                                                      // Wacht tot dat de echo een lage output heeft.

    long int travelTime = micros() - startTime;                                                 // Bereken de tijd tussen het begin van de hoge output en het einde.

    int distance = travelTime / 58;                                                             // Bereken de afstand in hele centimeters.

    return distance;                                                                            // Geef de afstand terug.
}
