/** MQTT Publish von Sensordaten */
#include "mbed.h"
#include "HTS221Sensor.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include "Motor.h"

#include "ISM43362Interface.h"
ISM43362Interface wifi( false );

// Internal I2C 2
static DevI2C devI2c( PB_11, PB_10 );
static HTS221Sensor hum_temp(&devI2c);
AnalogIn hallSensor( A3 );

// Topic's
char* topicTEMP =  "iotkit/sensor";
char* topicALERT = "iotkit/alert";
// MQTT Brocker
char* hostname = "broker.hivemq.com";
int port = 1883;
// MQTT Message
MQTT::Message message;
// I/O Buffer
char buf[100];

// Klassifikation 
char cls[3][10] = { "low", "middle", "high" };
int type = 0;

// UI
DigitalOut led1( LED1 );
DigitalOut alert( LED2 );

// Aktore(n)
Motor m1(D5, D6, D7); // M02: PWM, Vorwaerts, Rueckwarts
PwmOut speaker( D3 );

/** Hilfsfunktion zum Publizieren auf MQTT Broker */
void publish( MQTTNetwork &mqttNetwork, MQTT::Client<MQTTNetwork, Countdown> &client, char* topic )
{
    led1 = 1;
    printf("Connecting to %s:%d\r\n", hostname, port);
    
    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\r\n", rc);

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "mbed-sample";
    data.username.cstring = "testuser";
    data.password.cstring = "testpassword";
    if ((rc = client.connect(data)) != 0)
        printf("rc from MQTT connect is %d\r\n", rc);

    MQTT::Message message;    
    
    printf( "Topi: %s\n", topic );
    printf( "Push: %s\n", buf );
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) buf;
    message.payloadlen = strlen(buf)+1;
    client.publish( topic, message);  
    
    // Verbindung beenden, ansonsten ist nach 4x Schluss
    if ((rc = client.disconnect()) != 0)
        printf("rc from disconnect was %d\r\n", rc);

    mqttNetwork.disconnect();
    led1 = 0;
}

/** Hauptprogramm */
int main()
{
    uint8_t id;
    float temp, hum;
    alert = 0;
    
    printf( "MQTTPublish\r\n" );
    printf( "host: %s:%s\r\n", hostname, port );

    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    int ret = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\nConnection error\n");
        return -1;
    }

    // TCP/IP und MQTT initialisieren (muss in main erfolgen)
    MQTTNetwork mqttNetwork( &wifi );
    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);
    
    /* Init all sensors with default params */
    hum_temp.init(NULL);
    hum_temp.enable();    

    while   ( 1 ) 
    {
        // Temperator und Luftfeuchtigkeit
        hum_temp.read_id(&id);
        hum_temp.get_temperature(&temp);
        hum_temp.get_humidity(&hum);    
        if  ( type == 0 )
        {
            temp -= 5.0f;
            m1.speed( 0.0f );
        }
        else if  ( type == 2 )
        {
            temp += 5.0f;
            m1.speed( 1.0f );
        }
        else
        {
            m1.speed( 0.75f );
        }
        sprintf( buf, "0x%X,%2.2f,%2.1f,%s", id, temp, hum, cls[type] ); 
        type++;
        if  ( type > 2 )
            type = 0;       
        publish( mqttNetwork, client, topicTEMP );
        
        // alert Tuer offen 
        printf( "Hall %4.4f, alert %d\n", hallSensor.read(), alert.read() );
        if  ( hallSensor.read() > 0.6f )
        {
            // nur einmal Melden!, bis Reset
            if  ( alert.read() == 0 )
            {
                sprintf( buf, "alert: hall" );
                message.payload = (void*) buf;
                message.payloadlen = strlen(buf)+1;
                publish( mqttNetwork, client, topicALERT );
                alert = 1;
            }
            speaker.period( 1.0 / 3969.0 );      // 3969 = Tonfrequenz in Hz
            speaker = 0.5f;
            wait( 0.5f );
            speaker.period( 1.0 / 2800.0 );
            wait( 0.5f );
        }
        else
        {
            alert = 0;
            speaker = 0.0f;
        }
        wait    ( 2.0f );
    }
}
