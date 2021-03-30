#include "bridge.h"
#include "hardware.h"

int openBridge()
{
    for (unsigned int i = 0; i < 50; i += 2)
    {
        changeServoPosition(i);
        delay(200);
    }
    return 0;
}

int closeBridge()
{
    for (unsigned int i = 50; i > 0; i -= 2)
    {
        changeServoPosition(i);
        delay(200);
    }
    return 0;
}

void checkBoatDetection()
{
    int distance = getCurrentDistance();
    if (distance < 10)
    {
        if (openBridge() == 0)
            cout << "Bridge has been opened!" << endl;

        while (distance < 10)
            distance = getCurrentDistance();

        delay(5000);

        if (closeBridge() == 0)
            cout << "Bridge has been closed!" << endl;
    }

}