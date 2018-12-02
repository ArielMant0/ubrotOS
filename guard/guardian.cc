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
	g_cpu.enable_int();
	// Get assigned interrupt jandler
	Gate *g = &g_plugbox.report(slot);
	// Call its prologue
	if (g->prologue())
	{
		// Request corresponding epilogue
		g_guard.relay(g);
	}
}
