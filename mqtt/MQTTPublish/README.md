## MQTT Publish

Mittels Publish (unten) kann eine Meldung zum MQTT Broker bzw. Topic gesendet werden.

Ein anderes Board oder der Mosquitto Client mosquitto_sub kann dieses Topic Abonnieren (subscribe).

### Client

	mosquitto_sub -h iot.eclipse.org -t iotkit/#
		0xBC,23.80,26.3,low
		0xBC,28.80,26.3,middle
		0xBC,33.90,26.3,high
	
Abonnieren der MQTT Publish Meldungen via [Mosquitto](https://projects.eclipse.org/projects/technology.mosquitto) Client Utility mosquitto_sub.

### Links

*  [Arm Mbed Online Compiler](https://os.mbed.com/teams/Disco-L475VG-IOT/code/Disco_MQTTPublish/)
