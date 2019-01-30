/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ O R G A N I Z E R                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Organizer.                                  */
/*****************************************************************************/

#ifndef __Guarded_Organizer_include__
#define __Guarded_Organizer_include__

#include "syscall/thread.h"
#include "thread/organizer.h"

/**
 * Der Guarded_Organizer implementiert die Systemaufrufschnittstelle zum Organizer. 
 * Die von ihm angebotenen Methoden werden direkt auf die Methoden der Basisklasse abgebildet, 
 * nur dass ihre Ausführung jeweils mit Hilfe eines Objekts der Klasse Secure geschützt wird und 
 * dass nicht Customer, sondern Thread Objekte behandelt werden. 
 */
class Guarded_Organizer : public Organizer
{
private:
    Guarded_Organizer(const Guarded_Organizer &copy); // Verhindere Kopieren
public:
    Guarded_Organizer() {}

    /**
     * Mit dieser Methode wird der Prozess that beim Scheduler angemeldet.
     */
    void ready(Thread& that);

    /**
     * Hiermit kann sich ein Prozess selbst beenden.
     */
	void exit();

    /**
     * Mit dieser Methode kann ein Prozess einen anderen (that) beenden.
     */
	void kill(Thread& that);

    /**
     * Hiermit kann ein Prozesswechsel ausgelöst werden.
     */
	void resume();
};

extern Guarded_Organizer g_organizer;

#endif
