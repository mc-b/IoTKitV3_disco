/** Motor Beispiel
    Motoren an M01 und M02 einstecken.
*/
#include "mbed.h"
#include "Motor.h"

Motor m1(D3, D2, D4); // PWM, Vorwaerts, Rueckwarts
Motor m2(D5, D6, D7); // PWM, Vorwaerts, Rueckwarts

int main() 
{
    printf( "Motor Test\n" );
    while   ( 1 )
    {
        // rueckwaerts
        printf( "rueckwaerts\n" );
        for (float s = 0.7f; s < 1.0f ; s += 0.01f )
        {
           m1.speed(s * -1); 
           m2.speed(s);
           wait(0.2);
        }
        m1.speed( 0 );
        wait( 1.0 );
        
        printf( "vorwaerts\n" );        
        for (float s = 0.7f; s < 1.0f ; s += 0.01f )
        {
           m1.speed(s); 
           m2.speed(s * -1);
           wait(0.2);
        }
        m1.speed( 0 );
        m2.speed( 0 );
        wait( 1.0 );   
    }
}
