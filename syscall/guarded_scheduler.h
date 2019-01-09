/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S C H E D U L E R                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Scheduler.                                  */
/*****************************************************************************/

#ifndef __guarded_scheduler_include__
#define __guarded_scheduler_include__

#include "thread/scheduler.h"
#include "thread.h"
    
/**
 * Der Guarded_Scheduler implementiert die Systemaufrufschnittstelle zum Scheduler. Die von ihm 
 * angebotenen Methoden werden direkt auf die Methoden der Basisklasse abgebildet, nur dass ihre 
 * Ausführung jeweils mit Hilfe eines Objekts der Klasse Secure geschützt wird, und dass nicht 
 * Entrant-, sondern Thread-Objekte behandelt werden. 
 */    
class Guarded_Scheduler : public Scheduler
{

private:

    Guarded_Scheduler(const Guarded_Scheduler &copy); // Verhindere Kopieren

public:

    Guarded_Scheduler() {}

    // Mit dieser Methode wird der Prozess that beim Scheduler angemeldet.
    void ready(Thread &that);

    // Hiermit kann sich ein Prozess selbst beenden.
    void exit();

    // Mit dieser Methode kann ein Prozess einen anderen (that) beenden.
    void kill(Thread& that);

    // Hiermit kann ein Prozesswechsel ausgelöst werden.
    void resume();
};

extern Guarded_Scheduler g_scheduler;

#endif
