#include <stdio.h>
#include <wiringPi.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

#define LED1 11
#define LED2 27

int main (void)
{

  wiringPiSetup () ;

  pinMode (LED1, OUTPUT) ;
  pinMode (LED2, OUTPUT) ;

  for (;;)
  {
    digitalWrite (LED1, 1) ;
    digitalWrite (LED2, 1) ;     // On
    delay (500) ;               // mS
    digitalWrite (LED1, 0) ; 
    digitalWrite (LED2, 0) ;    // Off
    delay (500) ;
    
  }
  return 0 ;

}


