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
#include "machine/cpu.h"

Guard g_guard;

void Guard::leave()
{
	// Current interrupt handler
	Gate *gate = nullptr;
	// Run all epilogues currently in the queue
	while (true)
	{
		g_cpu.disable_int();
		gate = (Gate*)m_queue.dequeue();
		g_cpu.enable_int();
		if (gate == nullptr) {
			break;
		}

		gate->epilogue();
		gate->queued(false);
	}
	// Unlock again
	retne();
}

void Guard::relay(Gate *item)
{
	// If we can immediately run the epilogue, do so
	if (avail())
	{
		g_cpu.enable_int();
		enter();
		item->epilogue();
		retne();
	}
	// Otherwise queue the epilogue (interrupt handler)
	else if (!item->queued())
	{
		item->queued(true);
		m_queue.enqueue(item);
	}
}