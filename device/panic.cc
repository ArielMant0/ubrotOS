/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/

#include "device/panic.h"
#include "machine/cpu.h"
#include "device/cgastr.h"

Panic g_panic;

bool Panic::prologue()
{
	return true;
}

void Panic::epilogue()
{
	// Print some kind of error message
	kout << "Panic Trigger" << endl;
	// Halt the CPU
	g_cpu.halt();
}
