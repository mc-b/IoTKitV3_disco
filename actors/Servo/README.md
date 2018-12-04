## Servo (Aktor) 

![](../../images/actors/ServoOpen.png)

![](../../images/actors/ServoSignal.png)

[http://wiki.rc-network.de/Servo](http://wiki.rc-network.de/Servo)

- - -

Der Servo (auch Rudermaschine) hat die Aufgabe, entsprechend dem Signal, dass er vom Empfänger erhält, die Ruder (oder andere Komponenten am Modell) zu stellen.

Servo lassen sich, in der Regel, von 0 - 180° bewegen. Für die Ansteuerung wird ein PwmOut Signal mit einer fixen Periode von 20 Millisekunden verwendet.

Das Ruder wird mittels einer Pulsweite von ca. 900 - 2100 Microsekunden positioniert. 

	servo.period_ms( 20 );
	servo.pulsewidth_us( 900 + pos ); 

Es gibt analoge und digitale Servo&#039;s. Der Unterschied liegt darin, dass digitale Servo erst anfangen den Stellwinkel zu wechseln, wenn ein sauberes Signal anliegt.

Weitere Informationen und eine Ausführliche Einführung in Englisch [An Introduction to RC Servos](http://developer.mbed.org/users/4180_1/notebook/an-introduction-to-servos/)

### Anwendungen 

*   Steuerung von Roboterarmen
*   Modellflugzeuge
*   Schalten von Weichen auf der Modelleisenbahn

### Anschlussbelegung (Servo - Shield) 

Der Servo wird mit 5V betrieben und kann direkt auf einen der GND/+5V/S Header gesteckt werden. Das orange Kabel gehört auf S (Signal).

### Links

*  [Arm Mbed Online Compiler](https://os.mbed.com/compiler/#import:/teams/Disco-L475VG-IOT/code/Servo/)
