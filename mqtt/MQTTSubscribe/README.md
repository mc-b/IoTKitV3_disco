##   MQTT Subscribe (experiementell)

Mittels Subscribe kann ein Topic auf dem MQTT Broker abonniert werden.

Ein anderes Board oder der Mosquitto Client mosquitto_pub sendet an dieses Topic (publish).


### Client 

	mosquitto_pub -h broker.hivemq.com -t iotkit/light -m "1.28" -q 0


Publizieren von Daten auf dem MQTT Broker mittels des [Mosquitto](https://projects.eclipse.org/projects/technology.mosquitto) Client Utilities mosquitto_pub.

### Links

