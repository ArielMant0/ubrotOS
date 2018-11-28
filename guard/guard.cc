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

#include "guard/guard.h"

Guard g_guard;

void Guard::leave()
{
	retne();
	// Call all epilogues currently in the queue
	Gate *gate = nullptr;
	while ((gate = m_queue.dequeue()) != nullptr)
	{
		gate->epilogue();
	}
}

void Guard::relay(Gate *item)
{
	if (avail())
	{
		item->epilogue();
	}
	else if (!item->queued())
	{
		m_queue.enqueue(item);
		item->queued(true);
	}
}