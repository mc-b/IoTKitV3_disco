Software
--------

## Betriebssystem

Der IoTKit V3 verwendet [ARM mbed OS](https://www.mbed.com/en/platform/mbed-os/).

ARM mbed OS ist ein Open-Source-Embedded-Betriebssystem, das speziell für die "Dinge" im Internet der Dinge entwickelt wurde.

Es enthält alle Funktionen, die benötigt werden, um ein angeschlossenes Produkt auf Basis eines ARM Cortex-M Mikrocontrollers zu entwickeln, einschliesslich Sicherheit, Konnektivität, RTOS und Treiber für Sensoren und E / A-Geräte.

## Entwicklungsumgebung

Als Entwicklungsumgebung kann
* der [Arm Mbed Online Compiler (empfohlen)](https://os.mbed.com/compiler/)
* das [mbed CLI](https://github.com/ARMmbed/mbed-cli)

Wird der [Arm Mbed Online Compiler](https://os.mbed.com/compiler/) verwendet, ist der Sourcecode bzw. Link unten an der jeweiligen Seite, gekennzeichnet mit **Arm Mbed Online Compiler**, zu verwenden.

Ist kein Link **Arm Mbed Online Compiler** vorhanden, kann das [IoTKit V3 Template](https://os.mbed.com/teams/Disco-L475VG-IOT/code/template/) verwendet werden. Dabei ist der Inhalt von `main.cpp` mit dem Inhalt des Beispiels zu ersetzen.

### Installation und Quick Start mbed-cli und Eclipse

[mbed cli](https://github.com/ARMmbed/mbed-cli) mit allen Abhängigkeiten (Python, GCC_ARM) wie unter [Installation](https://github.com/ARMmbed/mbed-cli#installation) beschrieben, installieren.

Globale Konfigurationen für Board und Compiler setzen.

	mbed config --global TARGET DISCO_L475VG_IOT01A
	mbed config --global TOOLCHAIN GCC_ARM

Verzeichnis mbed erstellen, Projekt initialisieren und benötigte Libraries clonen:

	mkdir -p mbed475
	cd mbed475
	mbed new .
	
	# UI 
	mbed add http://developer.mbed.org/teams/smdiotkitch/code/OLEDDisplay/
	# Communication
	mbed add https://mbed.org/teams/mqtt/code/MQTT/
	mbed add https://github.com/ARMmbed/ntp-client.git
	mbed add https://os.mbed.com/teams/sandbox/code/mbed-http/
	mbed add https://os.mbed.com/teams/Disco-L475VG-IOT/code/wifi-ism43362/
	# Bluetooth
	mbed add https://developer.mbed.org/teams/Bluetooth-Low-Energy/code/BLE_API/
	mbed add https://mbed.org/teams/Nordic-Semiconductor/code/nRF51822/
	# Sensoren
	mbed add http://developer.mbed.org/users/AtomX/code/MFRC522/ 
	mbed add https://os.mbed.com/teams/IoTKitV3/code/HTS221lib/
	mbed add https://developer.mbed.org/teams/ST/code/LIS3MDL/
	mbed add https://developer.mbed.org/teams/ST/code/LSM6DSL/
	mbed add https://os.mbed.com/teams/ST/code/LPS22HB/
	mbed add https://os.mbed.com/teams/ST/code/VL53L0X/
	
Anschliessend eine Statische Library für mbed-os und alle obigen Libraries erstellen:

	mbed compile --library --no-archive --source=mbed-os --source OLEDDisplay \
	             --source MQTT --source ntp-client --source mbed-http \
	             --source BLE_API --source nRF51822 --source wifi-ism43362 \
	             --source HTS221lib --source MFRC522 --source LIS3MDL --source LSM6DSL --source LPS22HB --source VL53L0X \
	             --build=../mbed475-os
	
Zum Schluss IoTKitV3 Beispiele clonen

	git clone https://github.com/mc-b/IoTKitV3_disco.git
	
Die jeweiligen Beispiele können dann wie folgt compiliert werden, z.B. DigitalOut

	cd IoTKitV3_disco/gpio/DigitalOut
	mbed compile --source ../../../../mbed475-os/ --source . --build BUILD

Das compilierte Programm ist im Verzeichnis `BUILD` mit der Endung `.bin`, hier `BUILD/DigitalOut.bin` und kann einfach mittels Drag&Drop auf das Board bzw. dessen Laufwerk kopiert werden.

**Optional** Beispiele für Eclipse aufbereiten

	mbed export -i eclipse_gcc_arm
	
Anschliessend mittels File -> Import -> Existing Projects `mbed` Projekt in Workspace importieren.	

**Hinweise**:
* Da die Libraries statisch Compiliert sind, sind die Einträge in `mbed_app.json` bereits im Sourcecode aufgelöst und Änderungen haben evtl. keinen Einfluss mehr. Lösung: evtl. `mbed_app.json` in den Libraries vor dem Compilieren der statischen Libraries entsprechend anpassen.
* Als Nachteil für das schnellere Compilieren, ist zu Erwähnen, dass die Programme grösser sind als normal, weil alle Libraries mit verlinkt werden.

#### Serielle Console

Die mbed CLI beinhaltet ein Terminalprogramm um die Ausgabe via Serieller Schnittstelle des mbed Boards auszugeben.

	mbed sterm

### Links

* Terminalemulations Programme: [Windows](http://sourceforge.jp/projects/ttssh2/releases/), [Mac](http://freeware.the-meiers.org/), [Linux](http://manpages.ubuntu.com/manpages/vivid/man8/picocom.8.html)
* [PC Driver (nur Windows)](https://os.mbed.com/handbook/Windows-serial-configuration)
