/** Roboter Beispiele mit Motor und Servos
*/

#include "mbed.h"
#include "OLEDDisplay.h"

// Display
OLEDDisplay oled;

// Servos
PwmOut foot( D6 );
PwmOut base( D9 );
PwmOut arm( D10 );
PwmOut pincer( D11 );

// Max pulsewidth Servo = 0.0 - 1.0
#define MIN			800
#define MAX         2100

// Move Positionen
float footLeft = 0.2f;
float footRight = 0.8f;
float baseUp = 0.4f;
float baseDown = 0.1f;
float armUp = 0.8f;
float armDown = 0.1f;
float pincerOpen = 0.8f;
float pincerClose = 0.2f;

/** Servo langsam bewegen */
void servoMove( PwmOut &servo, float start, float end )
{
    if  ( start < end )
    {
        for ( float i = start; i < end; i += 0.0005f )
        {
            servo.pulsewidth_us( ((MAX-MIN) * i) + MIN );
            wait    ( 0.004f );
        }
    }
    else
    {
        for ( float i = start; i > end; i -= 0.0005f )
        {
            servo.pulsewidth_us( ((MAX-MIN) * i) + MIN );
            wait    ( 0.004f );
        }        
    }
}

/** Hauptprogramm */
int main()
{
	foot.period_ms(20);
	base.period_ms(20);
	arm.period_ms(20);
	pincer.period_ms(20);

    while   ( 1 )
    {
        oled.clear();
    	oled.printf( "up - open pincer\n");
        servoMove( arm, armDown, armUp );
        servoMove( base, baseDown, baseUp );
        servoMove( pincer, pincerClose, pincerOpen );    // open
        servoMove( foot, footLeft, footRight );
        wait( 0.5f );

    	oled.clear();
    	oled.printf( "down - close pincer\n");
        servoMove( base, baseUp, baseDown );
        servoMove( arm, armUp, armDown );
        servoMove( pincer, pincerOpen, pincerClose );    // close
        wait( 0.5f );

    	oled.clear();
    	oled.printf( "up - close pincer\n");
        servoMove( arm, armDown, armUp );
        servoMove( base, baseDown, baseUp );        
        servoMove( foot, footRight, footLeft );
        wait( 0.5f );
        
        oled.clear();
    	oled.printf( "down - open pincer\n");
        servoMove( base, baseUp, baseDown );
        servoMove( arm, armUp, armDown );
        servoMove( pincer, pincerClose, pincerOpen );    // open
        wait( 0.5f );

     }
}
