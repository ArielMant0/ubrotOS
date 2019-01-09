/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__

#include "io_port.h"

/**
 * Die Klasse PIT steuert den Programmable Interval Timer (PIT) des PCs.
 */
class PIT
{

private:

    PIT(const PIT &copy); // Verhindere Kopieren

    IO_Port m_count1, m_control;
    int m_interval;

    enum Counter { first=0, second, third, control };
    enum ReadWrite { latch=0, low, high, lowhigh };
    enum Mode { 
    	single=0,
    	singleHard,
    	periodic,
    	periodicHard,
    	rectangle,
    	software,
    	hardware
    };
    enum Format { binary=0, bcd };

    void setTimer(PIT::Counter which, int us);

public:

	/**
	 * Im Konstruktor wird der Timer so initialisiert, dass er in Abständen von ca. us Mikrosekunden
	 * regelmäßig Unterbrechungen auslöst. Da die Auflösung des Timerbausteins maximal 838 
	 * Nanosekunden beträgt, ist keine ganz exakte Einstellung im Mikrosekundenbereich möglich.
	 */
    PIT (int us) : m_count1(0x40), m_control(0x43) {
      interval (us);
    }

    int frequency(int us) {
        return 1000000 / us;
    }

    // Gibt an, welches Unterbrechungsintervall eingestellt wurde.
    int interval () {
    	return m_interval;
    }

    // Stellt das Unterbrechungsintervall neu ein.
    void interval (int us);
};

#endif
