/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse koennen Aktivitaeten, die einen kritischen        */
/* Abschnitt betreffen, der mit einem Guard-Objekt geschuetzt ist, mit       */
/* Unterbrechungsbehandlungsroutinen synchronisiert werden, die ebenfalls    */
/* auf den kritischen Abschnitt zugreifen.                                   */
/*****************************************************************************/

#ifndef __Guard_include__
#define __Guard_include__

#include "object/queue.h"
#include "guard/gate.h"
#include "guard/locker.h"
        
class Guard : public Locker
{
private:

	Queue m_queue;

    Guard (const Guard &copy); // Verhindere Kopieren
public:

    Guard () {}

    void leave ();

	void relay (Gate* item);
};

extern Guard g_guard;

#endif
