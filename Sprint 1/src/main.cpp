#include <hardware.h>


void testHardware()
{
    int x = 0;
    while (x < 10000)
    {
        int distance = afstandSensor();
        cout << "Distance in cm: " << distance << endl;
        delay(500);
        x++;
    }

    if (servo(40) != 0)
        cout << "Servo werkt niet!" << endl;
    
}



int main()
{
    testHardware();
    

}