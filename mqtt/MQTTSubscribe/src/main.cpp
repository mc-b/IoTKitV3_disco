/** MQTT Subscribe */
#include "mbed.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include "OLEDDisplay.h"

#include "ISM43362Interface.h"
ISM43362Interface wifi( false );

// Topic's
char* topicLight = "iotkit/light";
// MQTT Brocker
char* hostname = "broker.hivemq.com";
int port = 1883;

// UI
OLEDDisplay oled;
DigitalOut led1( LED1 );

void messageArrived( MQTT::MessageData& md )
{
    MQTT::Message &message = md.message;
    printf("Message arrived: qos %d, retained %d, dup %d, packetid %d\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\n", message.payloadlen, (char*) message.payload);
}

int main()
{
    oled.clear();
    oled.printf( "MQTTSubscribe\r\n" );
    oled.printf( "host: %s:%d\r\n", hostname, port );
    
    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    oled.printf( "SSID: %s\r\n", MBED_CONF_APP_WIFI_SSID );
    int ret = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\nConnection error: %d\n", ret);
        return -1;
    }

    // TCP/IP und MQTT initialisieren (muss in main erfolgen)
    MQTTNetwork mqttNetwork( &wifi );
    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);

    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\r\n", rc);
 
    // mit MQTT Broker verbinden
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
    data.MQTTVersion = 3;
    data.clientID.cstring = "mbed-sample";
    data.username.cstring = "testuser";
    data.password.cstring = "testpassword";
    
    if ((rc = client.connect(data)) != 0)
        printf("rc from MQTT connect is %d\r\n", rc);

    rc = client.subscribe( topicLight, MQTT::QOS0, messageArrived );
    printf("rc from MQTT subscribe is %d\n", rc);

    while   ( 1 )
    {
        led1 = 0;
        client.yield(1000);         // MQTT Client darf empfangen
        led1 = 1;
        wait( 1.0 );
    }
    
    if ((rc = client.unsubscribe(topicLight)) != 0)
        printf("rc from unsubscribe was %d\n", rc);
    
    if ((rc = client.disconnect()) != 0)
        printf("rc from disconnect was %d\n", rc);
    
    mqttNetwork.disconnect();
    return 0;
}
