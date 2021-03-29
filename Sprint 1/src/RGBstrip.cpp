#include <iostream>
#include <wiringPi.h>
#include <vector>

using namespace std;

int clockpin = 10;
int infopin = 11;


pinMode(clockpin, OUTPUT);
pinMode(infopin, OUTPUT);


vector<vector<int>> ledarray = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

vector<int> translate(string input)
{
    if (input == "red")
        return vector<int>{0, 0, 255};
    if (input == "orange")
        return vector<int>{0, 50, 255};
    if (input == "yellow")
        return vector<int>{0, 100, 255};
    if (input == "green")
        return vector<int>{0, 255, 0};
    if (input == "lblue")
        return vector<int>{255, 255, 0};
    if (input == "blue")
        return vector<int>{255, 0, 0};
    if (input == "purple")
        return vector<int>{255, 0, 255};
    if (input == "white")
        return vector<int>{255, 255, 255};
    if (input == "black")
        return vector<int>{0, 0, 0};
}

vector<bool> binearmaker(int num, vector<bool> &end)
{
    int i = 128;
    while (i > 0)
    {
        end.push_back(num >= i);
        if (num >= i)
            num -= i;
        i = i >> 1;
    }
    return end;
}

void ledcall(int pos, string color)
{
    ledarray[pos] = translate(color);
    digitalWrite(infopin, LOW);
    for (int i = 0; i < 32; i++)
    {
        digitalWrite(clockpin, HIGH);
        digitalWrite(clockpin, LOW);
    }
    for (int i = 0; i < ledarray.size(); i++)
    {
        vector<bool> led = {1, 1, 1, 0, 0, 0, 1, 0};
        for (int j = 0; j < ledarray[i].size(); j++)
        {
            binearmaker(ledarray[i][j], led);
        }
        for (int j = 0; j < led.size(); j++)
        {
            if (led[j])
                digitalWrite(infopin, HIGH);
            digitalWrite(clockpin, HIGH);
            digitalWrite(clockpin, LOW);
            digitalWrite(infopin, LOW);
        }
    }
}

int main()
{
    ledcall(0, "yellow");
    ledcall(3, "white");
    ledcall(7, "green");
}