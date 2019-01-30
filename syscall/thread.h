/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             T H R E A D                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Benutzerschnittstelle eines Threads.                                      */
/*****************************************************************************/

#ifndef __thread_include__
#define __thread_include__

#include "thread/customer.h"

/**
 * Die Klasse Thread implementiert die Benutzerschnittstelle eines Fadens. Zur Zeit ist Thread
 * nichts weiter als ein neuer Name für die Klasse Entrant.
 */
class Thread : public Customer
{

private:

    Thread (const Thread &copy); // Verhindere Kopieren

public:

	// Der Konstruktor leitet den Parameter tos an den Konstruktor der Basisklasse 
	// Customer weiter. 	
	Thread (void* tos) : Customer(tos) {}
          
};

#endif
