/** Zahlfallszahlen erzeugen und damit Fernsehsimulator fuettern
*/
#include "mbed.h"
#include <time.h>

DigitalOut led[] =  { DigitalOut( LED1 ), DigitalOut( LED2 ), DigitalOut( LED3 ), DigitalOut( LED4 ) };

int main()
{
    printf( "Fernsehsimulator\n" );
     
    time_t t;
    time(&t);
    srand( (unsigned int)t );              /* Zufallsgenerator initialisieren */

    while   ( 1 )
    {
        for ( int i = 0; i < 4; i++ )
        {
            int r = rand();
            led[i] = ( (r % (i+2) ) != 0 ) ? 1 : 0;
        }
            
        wait( 0.2f );          
    }
}
