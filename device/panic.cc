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

void Panic::trigger()
{
	kout << "Panic Trigger" << endl;

	//g_cpu.idle();
} 
