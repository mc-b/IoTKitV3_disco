/** Ausgabe auf allen Seriellen Schnttstellen auf dem IoTKit V3
*/
#include "mbed.h"

// Beispiel 4 x UART - variert je nach Board
Serial serial[] = { Serial( USBTX, USBRX ), Serial( A1, A0 ), Serial( D1, D0 ), Serial( A4, A5 ) };

int main()
{
    for ( int i = 0; i < 4; i++ )
        serial[i].printf( "SerialAll auf Serial %d\r\n", i );
     
    int count = 0;    
    while   ( 1 )
    {
        for ( int i = 0; i < 4; i++ )
            serial[i].printf( "Counter %d auf Serial %d\r\n", count, i );
        count++;
        wait( 2.0 );            
    }
}                   
