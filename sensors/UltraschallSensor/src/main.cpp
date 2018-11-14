/** Ultraschall Abstandsmesser 
 */
#include "mbed.h"
#include "ultrasonic.h"
 
 void dist(int distance)
{
    // Abhandlung der Entfernung
    printf("Entfernung %dmm\n", distance);
}
 
ultrasonic mu(A5, A4, .1, 1, &dist);    // setzt den Trigger Pin auf A5, den Echo Pin auf A4
                                        // liefert all 0.1 Sekunten einen neuen Wert mit einem
                                        // Timeout von 1 Sekunden. Fuer die Ausgabe des Wertes
                                        // wird die Funktion dist aufgerufen.
int main()
{
    mu.startUpdates();                  // Start der Abstandsmessung
    while(1)
    {
        mu.checkDistance();             // Pooling vom Distanzmesser, sollte moeglichst oft erfolgen
        // weitere Abhandlungen
    }
}         
