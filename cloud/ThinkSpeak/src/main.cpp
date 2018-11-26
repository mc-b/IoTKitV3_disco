/** Beispiel Senden von Sensordaten an ThingSpeak
 */
#include "mbed.h"
#include "HTS221Sensor.h"
#include "http_request.h"
#include "network-helper.h"
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled;

static DevI2C devI2c( PB_11, PB_10 );
static HTS221Sensor hum_temp(&devI2c);

/** ThingSpeak URL und API Key ggf. anpassen */
char host[] = "https://api.thingspeak.com/update.json";
char key[] = "A2ABBMDJYRAMA6JM";

// I/O Buffer
char message[6000];

DigitalOut myled(LED1);

int main()
{
    uint8_t id;
    float value1, value2;

    printf("\tThingSpeak\n");

    /* Init all sensors with default params */
    hum_temp.init(NULL);
    hum_temp.enable();

    hum_temp.read_id(&id);
    printf("HTS221  humidity & temperature    = 0x%X\r\n", id);

    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* network = connect_to_default_network_interface();
    
    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    while( 1 )
    {
        hum_temp.get_temperature(&value1);
        hum_temp.get_humidity(&value2);
        sprintf( message, "key=%s\nfield1=%.2f\nfield2=%.2f%%\n", key, value1, value2 );
        oled.cursor( 1, 0 );
        oled.printf( "temp: %3.2f\nhum : %3.2f", value1, value2 );

        myled = 1;
        HttpRequest* post_req = new HttpRequest( network, HTTP_POST, host );
        //post_req->set_header("Content-Type", "application/x-www-form-urlencoded");

        HttpResponse* post_res = post_req->send( message, strlen(message) );
        if (!post_res)
        {
            printf("HttpRequest failed (error code %d)\n", post_req->get_error());
            return 1;
        }
        printf("\n----- HTTP POST response -----\n");
        delete post_req;
        myled = 0;
        wait(10);
    }
}
