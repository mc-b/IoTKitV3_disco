WLAN (WiFi)
-------------------

[Wireless Local Area Network](https://de.wikipedia.org/wiki/Wireless_Local_Area_Network) (Wireless LAN bzw. W-LAN, meist WLAN; deutsch drahtloses lokales Netzwerk) bezeichnet ein lokales Funknetz, wobei meist ein Standard der IEEE-802.11-Familie gemeint ist. Für diese engere Bedeutung ist in manchen Ländern (z. B. USA, Großbritannien, Kanada, Niederlande, Spanien, Frankreich, Italien) weitläufig beziehungsweise auch synonym der Begriff Wi-Fi gebräuchlich. 

Der IoTKit V3 wird mittels dem [Wi-Fi® module Inventek ISM43362-M3G-L44](https://www.inventeksys.com/wifi/wifi-modules/ism4336-m3g-l44-e-embedded-serial-to-wifi-module/) ans Internet angeschlossen.

### Beispiele

* [WiFi](wifi/)
* [NTP - Zeit setzen via Internet](NTPV2/)

### Konfiguration

Die eigentliche Konfiguration der Schnittstelle erfolgt in der Datei `mbed_app.json`. Die sehen Einträge wie folgt aus:

	{
	    "config": {
	        "wifi-shield": {
	            "help": "Options are internal, WIFI_ESP8266, WIFI_IDW0XX1",
	            "value": "WIFI_ISM43362"
	        },
	        "wifi-ssid": {
	            "help": "WiFi SSID",
	            "value": "\"LERNKUBE\""
	        },
	        "wifi-password": {
	            "help": "WiFi Password",
	            "value": "\"l3rnk4b3\""
	        },
	        "wifi-spi_miso": {
	            "help": "SPI-MISO connection to external device",
	            "value": "PC_11"
	        },
	        "wifi-spi_mosi": {
	            "help": "SPI-MOSI connection to external device",
	            "value": "PC_12"
	        },
	        "wifi-spi_sclk": {
	            "help": "SPI-CLOCK connection to external device",
	            "value": "PC_10"
	        },
	        "wifi-spi_nss": {
	            "help": "SPI chip select of external device",
	            "value": "PE_0"
	        },
	        "wifi-reset": {
	            "help": "WIFI module reset pin",
	            "value": "PE_8"
	        },
	        "wifi-dataready": {
	            "help": "WIFI module data ready pin",
	            "value": "PE_1"
	        },
	        "wifi-wakeup": {
	            "help": "WIFI module wakeup pin",
	            "value": "PB_13"
	        }
	    },
	    "target_overrides": {
	        "*": {
	            "platform.stdio-convert-newlines": true
	        },
	        "DISCO_L475VG_IOT01A": {
	            "ism43362.wifi-miso": "PC_11",
	            "ism43362.wifi-mosi": "PC_12",
	            "ism43362.wifi-sclk": "PC_10",
	            "ism43362.wifi-nss": "PE_0",
	            "ism43362.wifi-reset": "PE_8",
	            "ism43362.wifi-dataready": "PE_1",
	            "ism43362.wifi-wakeup": "PB_13",
	            "ism43362.provide-default": true
	        }        
	    }
	}
	
#### Links

* [The mbed OS configuration system](https://os.mbed.com/docs/v5.10/reference/configuration.html)	