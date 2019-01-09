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

#include "thread/entrant.h"

/**
 * Die Klasse Thread implementiert die Benutzerschnittstelle eines Fadens. Zur Zeit ist Thread
 * nichts weiter als ein neuer Name für die Klasse Entrant.
 */
class Thread : public Entrant
{

private:

    Thread (const Thread &copy); // Verhindere Kopieren

public:

	// Der Konstruktor leitet den Parameter tos an den Konstruktor der Basisklasse 
	// Entrant weiter. 	
	Thread (void* tos) : Entrant(tos) {}
          
};

#endif
