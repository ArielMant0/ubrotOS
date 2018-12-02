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
	// Call all epilogues currently in the queue
	Gate *gate = nullptr;
	while (avail() && (gate = (Gate*)m_queue.dequeue()) != nullptr)
	{
		gate->epilogue();
	}
	// Leave epilogue plane
	retne();
}

void Guard::relay(Gate *item)
{
	// If we can gp to the epilogue plane, do it
	if (avail())
	{
		item->epilogue();

	}
	// Otherwise queue the interrupt handler
	else if (!item->queued())
	{
		item->queued(true);
		m_queue.enqueue(item);
	}
}