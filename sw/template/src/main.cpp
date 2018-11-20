/** IOTKit V3 Template
*/
#include "mbed.h"

// UI, Input und Output
#include "OLEDDisplay.h"

OLEDDisplay oled;

// Kommunikation
#include "TCPSocket.h"
#include "NTPClient.h"

#include "ISM43362Interface.h"

ISM43362Interface wifi( false );

// DigitalIn button( USER_BUTTON1 );
// DigitalOut buzzer( D3 );

// Sensoren
//#include "MFRC522.h"
//#include "HTS221Sensor.h"
//#include "LPS22HBSensor.h"
//#include "lis3mdl_class.h"
//#include "LSM6DSLSensor.h"
//#include "VL53L0X.h"

//DevI2C devI2c( PB_11, PB_10 );
//HTS221Sensor hum_temp( &devI2c );
//LPS22HBSensor press_temp(&devI2c);
//LIS3MDL magnetometer(&devI2c);
//LSM6DSLSensor acc_gyro( &devI2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW );
//DigitalOut shutdown_pin(PC_6);
//VL53L0X range(&devI2c, &shutdown_pin, PC_7);
//MFRC522 rfidReader( D11, D12, D13, D10, D8 );
//AnalogIn hallSensor( A3 );

// Aktoren
//#include "Motor.h"
//Motor m1(D3, D2, D4); // PWM, Vorwaerts, Rueckwarts
//Motor m2(D5, D6, D7); // PWM, Vorwaerts, Rueckwarts

/**
 *  Hauptprogramm
 */
int main()
{
    oled.clear();
    oled.printf( "IoTKit V3 Template\n" );

#ifdef MBED_MAJOR_VERSION
    oled.printf("Mbed OS V: %d.%d.%d\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

    // Wifi Verbinden
    oled.printf("Con to %s\n", MBED_CONF_APP_WIFI_SSID);
    if  ( wifi.connect( MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2 ) != 0 )
        return ( -1 );

    // hole und setze Zeit vom Internet
    NTPClient ntp( &wifi) ;
    time_t timestamp = ntp.get_timestamp();
    if ( timestamp < 0 )
        return ( -1 );
    set_time( timestamp );

    while (true)
    {
       time_t seconds = time(NULL);
       oled.cursor( 2, 0 );
       oled.printf( "Date/Time %s UTC", ctime(&seconds) );

       wait( 1.0f );
    }
}
