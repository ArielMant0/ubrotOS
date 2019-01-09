/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ S C H E D U L E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Scheduler.                                  */
/*****************************************************************************/

#include "guarded_scheduler.h"
#include "guard/secure.h"

Guarded_Scheduler g_scheduler;

void Guarded_Scheduler::ready(Thread &that) {
	Secure lock;
	Scheduler::ready(that);
}

void Guarded_Scheduler::exit() {
	Secure lock;
	Scheduler::exit();
}

void Guarded_Scheduler::kill(Thread& that) {
	Secure lock;
	Scheduler::kill(that);
}

void Guarded_Scheduler::resume() {
	Secure lock;
	Scheduler::resume();
}

