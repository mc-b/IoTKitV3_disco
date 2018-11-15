/** Beispiel RGB LED Strip 5 Volt Variante mit einer Leitung pro Farbe
 *  Einstecken am STEPPER1+. +5V kommt an +, die anderen an D3, D5, D6.
*/
#include "mbed.h"

PwmOut green( D3 );
PwmOut red( D5 );
PwmOut blue( D6 );

void off()
{
    printf( "off \n" );
    red = 0;
    green = 0;
    blue = 0;
    wait( 1.0 );
}

void dim( PwmOut& pin )
{
    printf( "dim\n" );
    for ( float i = 0.0f; i < 1.0f; i += .01f )
    {
        pin = i;
        wait( 0.02 );
    }
    wait( 1.0 );
    
}

int main() 
{
    while   ( true )
    {
        dim( red );
        off();
        dim( green );
        off();
        dim( blue );
        off();
        
        red = 1;
        wait( 1.0 );
        off();
        
        green = 1;
        wait( 1.0 );
        off();
        
        blue = 1;
        wait( 1.0 );
        off();
        
        red = 1;
        blue = 1;
        green = 1;
        wait( 1.0 );
        off();
    }
}
