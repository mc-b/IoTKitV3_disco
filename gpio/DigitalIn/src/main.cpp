/** DigitalIn liest den Status eines Pins aus.
*/
#include <mbed.h>

DigitalIn button1( USER_BUTTON, PullUp );
DigitalOut led1( LED1 );

int main()
{
    while   ( 1 ) 
    {
        led1 = 0;
        if  ( button1 == 0 ) 
        {
            led1 = 1;
            wait( 1.0 );
        }

    }
}
