/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              G U A R D I A N                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Zentrale Unterbrechungsbehandlungsroutine des Systems.                    */
/* Der Parameter gibt die Nummer des aufgetretenen Interrupts an.            */
/*****************************************************************************/

/* INCLUDES */
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "guard/guard.h"

extern CGA_Stream kout;

extern "C" void guardian (unsigned int slot);

/* GUARDIAN: Low-Level Interrupt-Behandlung. Die Funktion wird spaeter noch */
/*           erweitert.                                                     */

void guardian (unsigned int slot)
{
	// hier ausgabe hin packen
	if (slot == (unsigned int) g_plugbox.keyboard || 
		slot == (unsigned int) g_plugbox.timer)
	{

		Gate g = g_plugbox.report(slot)
		if (g_guard.avail())
		{
			g_guard.enter();
			if (g.prologue())
			{
				g_guard.relay(&g);
			}
		}
	}
	else
	{
		kout << "Interrupt " << slot << " detected" << endl;
	}
}
