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
	// Unlock again
	retne();
	// Current interrupt handler
	Gate *gate = nullptr;
	// Run all epilogues currently in the queue
	while (avail() && (gate = (Gate*)m_queue.dequeue()) != nullptr)
	{
		gate->epilogue();
		gate->queued(false);
	}
}

void Guard::relay(Gate *item)
{
	// If we can immediately run the epilogue, do so
	if (avail())
	{
		item->epilogue();
	}
	// Otherwise queue the epilogue (interrupt handler)
	else if (!item->queued())
	{
		item->queued(true);
		m_queue.enqueue(item);
	}
}