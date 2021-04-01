#include <iostream>
#include <wiringPi.h>
#include <vector>
#include <unistd.h>

using namespace std;

int clockpin = 10;
int infopin = 6;

void setup()
{
    wiringPiSetup();
    pinMode(clockpin, OUTPUT);
    pinMode(infopin, OUTPUT);
}

vector<vector<int>> ledarray = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
string cstate = "green";

vector<int> translate(string input) //  vertalen van een string naar een RGB waarde.
{
    if (input == "red")
        return vector<int>{0, 0, 255};
    else if (input == "orange")
        return vector<int>{0, 50, 255};
    else if (input == "yellow")
        return vector<int>{0, 100, 255};
    else if (input == "green")
        return vector<int>{0, 255, 0};
    else if (input == "lblue")
        return vector<int>{255, 255, 0};
    else if (input == "blue")
        return vector<int>{255, 0, 0};
    else if (input == "purple")
        return vector<int>{255, 0, 255};
    else if (input == "white")
        return vector<int>{255, 255, 255};
    else // black
        return vector<int>{0, 0, 0};
}

void binearmaker(int num, vector<bool> &end) // maakt van de waarde num naar een 8 bit vector.
{
    int i = 128;
    while (i > 0)
    {
        end.push_back(num >= i);
        if (num >= i)
            num -= i;
        i = i >> 1;
    }
}

void ledcall(int pos, string color)
{
    ledarray[pos] = translate(color); // maakt van de string een waarde in de ledarray
    digitalWrite(infopin, LOW);
    for (int i = 0; i < 32; i++) // 32 nullen
    {
        digitalWrite(clockpin, HIGH);
        digitalWrite(clockpin, LOW);
    }
    for (int i = 0; i < ledarray.size(); i++) // loop langs alle leds
    {
        vector<bool> led = {1, 1, 1, 0, 0, 0, 1, 0}; // zet de felheid op "2"
        for (int j = 0; j < ledarray[i].size(); j++) // loop dor de RGB waardes van een inviduele led.
        {
            binearmaker(ledarray[i][j], led); // maakt er een vector met 32 waardes van.
        }
        for (int k = 0; k < led.size(); k++) // loopt door alle 32 bits voor een enkele led heen en stuurt die op.
        {
            if (led[k])
                digitalWrite(infopin, HIGH);
            digitalWrite(clockpin, HIGH);
            digitalWrite(clockpin, LOW);
            digitalWrite(infopin, LOW);
        }
    }
}

void stoplight(string state) // stuur "green" of "red" op om naar die kleur te laten lopen.
{
    while (cstate != state) // ga door tot dat de leds de kleur zijn die gevraagt word.
    {
        if (cstate == "green")
        {
            cstate = "yellow";  // maakt van "green" naar "yellow"
        }
        else
        {
            cstate = state; // maakt van "yellow" naar "red" en van "red" naar "green"
        }
        ledcall(7,cstate); // zet de leds naar de juiste kleur
        ledcall(1,cstate);
        ledcall(2,cstate);
        ledcall(3,cstate);
        ledcall(4,cstate);
        ledcall(5,cstate);
        ledcall(6,cstate);
        ledcall(0,cstate);
        if (cstate != state) // slaap als het naar red toe moet.
            usleep(1000000);
    }
}

int main()
{
    setup();
    ledcall(7,cstate);
    ledcall(1,cstate);
    ledcall(2,cstate);
    ledcall(3,cstate);
    ledcall(4,cstate);
    ledcall(5,cstate);
    ledcall(6,cstate);
    ledcall(0,cstate);
    while (true) // loop er lekker door heen.
    {
        usleep(10000000);
        stoplight("red");
        usleep(10000000);
        stoplight("green");
    }
}