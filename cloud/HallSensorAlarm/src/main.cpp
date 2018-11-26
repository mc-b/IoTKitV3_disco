/** Hall Sensor - Alarm via IFTTT
*/
#include "mbed.h"
#include "HTTPClient.h"
#include "data/HTTPText.h"
#include "EthernetInterface.h"
#include "OLEDDisplay.h"

OLEDDisplay oled;

AnalogIn hallSensor( A3 );
DigitalOut led1( LED1 );
DigitalOut led2( LED2 );
DigitalIn reset( USER_BUTTON );

// HTTP Hilfsklassen
EthernetInterface eth;
HTTPClient http;
char *finishMsg = "https://maker.ifttt.com/trigger/cooker_finish/with/key/mY3_IZhJSfm-tj3UVytotaqtD1L5AIEUMcal8nDy4dJ";
// I/O Buffer
char message[256];

int main()
{
    // Ethernet
    eth.init();
    eth.connect();
    
    led1 = 0;
    led2 = 1;
    oled.clear();
    oled.printf( "Hall Sensor Alarm" );
        
    while(1) 
    {
        // Alarm scharf
        if  ( led1 == 0 )
        {
            oled.cursor( 1, 0 );
            oled.printf( "scharf      " );
            float value = hallSensor.read();
            if  ( value < 0.4f || value > 0.6f )
            {
                oled.cursor( 1, 0 );
                oled.printf( "ALARM !!!" );
                http.get( finishMsg, message, sizeof(message) );
                led1 = 1;
                led2 = 0;
            }
        }
        else
        {
            if  ( reset == 0 )
            {
                oled.cursor( 1, 0 );
                oled.printf( "reset       " );                
                led1 = 0;
                led2 = 1;
            }
        }
        wait( 0.2f );
    }
}                                       
    
