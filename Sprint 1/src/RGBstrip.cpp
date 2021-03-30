#include <iostream>
// #include <wiringPi.h>
#include <vector>
#include <time.h>

using namespace std;

int clockpin = 31;
int infopin = 26;

void setup()
{
    // wiringPiSetup();
    // pinMode(clockpin, OUTPUT);
    // pinMode(infopin, OUTPUT);
}

vector<vector<int>> ledarray = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
string cstate = "green";

vector<int> translate(string input)
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

void binearmaker(int num, vector<bool> &end)
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
    ledarray[pos] = translate(color);
    // digitalWrite(infopin, LOW);
    for (int i = 0; i < 32; i++)
    {
        // digitalWrite(clockpin, HIGH);
        // digitalWrite(clockpin, LOW);
    }
    for (int i = 0; i < ledarray.size(); i++)
    {
        vector<bool> led = {1, 1, 1, 0, 0, 0, 1, 0};
        for (int j = 0; j < ledarray[i].size(); j++)
        {
            binearmaker(ledarray[i][j], led);
        }
        for (int k = 0; k < led.size(); k++)
        {
            // if (led[k])
            //     digitalWrite(infopin, HIGH);
            // digitalWrite(clockpin, HIGH);
            // digitalWrite(clockpin, LOW);
            // digitalWrite(infopin, LOW);
        }
    }
}

void stoplight(string state)
{
    if (cstate != state)
    {
        if (cstate == "red") { cstate = "yellow"; }
        else if (cstate == "yellow") { cstate = state; }
        else if (cstate == "green") { cstate = "yellow"; }
    }
    ledcall(0,cstate);
    ledcall(1,cstate);
    ledcall(2,cstate);
    ledcall(3,cstate);
    ledcall(4,cstate);
    ledcall(5,cstate);
    ledcall(6,cstate);
    ledcall(7,cstate);
}

int main()
{
    setup();
    // while (cstate != "red")
    // {
    //     stoplight("red");
    //     cout << cstate << "\n";
    // }
    while (true)
    {
        // stoplight("green");
        // cout << cstate << "\n";
        cout << mktime(struct tm gmtime) << " ";
    }
}