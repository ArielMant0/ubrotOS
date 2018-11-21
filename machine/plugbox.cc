/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Behandlungs- */
/* routine fuer jeden Hardware-, Softwareinterrupt und jede Prozessor-       */
/* exception festlegen.                                                      */
/*****************************************************************************/

#include "machine/plugbox.h"
#include "device/panic.h"

PlugBox g_plugbox;

PlugBox::PlugBox ()
{
	for (int i = 0; i < GATE_NUM; i++) 
	{
		m_gates[i] = &g_panic;
	}
}

void PlugBox::assign (unsigned int slot, Gate& gate)
{
	m_gates[slot] = &gate;
}

Gate& PlugBox::report (unsigned int slot)
{
	// TODO range check
	return *m_gates[slot];
}
