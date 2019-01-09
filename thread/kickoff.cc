/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K I C K O F F                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Funktion zum Starten einer Koroutine.                                     */
/* Da diese Funktion nicht wirklich aufgerufen, sondern nur durch eine       */
/* geschickte Initialisierung des Stacks der Koroutine angesprungen wird,    */
/* darf sie nie terminieren. Anderenfalls wuerde ein sinnloser Wert als      */
/* Ruecksprungadresse interpretiert werden und der Rechner abstuerzen.       */
/*****************************************************************************/

#include "thread/coroutine.h"
#include "guard/guard.h"

void kickoff (
	void *dummy1,
	void *dummy2,
	void *dummy3,
	void *dummy4,
	void *dummy5,
	void *dummy6,
	void* object
) {
	g_guard.leave();
	// Call coroutine (start) function
	((Coroutine*)object)->action();
	// This function should not terminate?
	while (true) {}
}
