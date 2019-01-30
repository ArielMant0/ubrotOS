/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        G U A R D E D _ B U Z Z E R                        */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Schnittstelle von Anwendungsthreads zu Buzzer-Objekten.                   */
/*****************************************************************************/

/* INCLUDES */

#include "syscall/guarded_buzzer.h"

void Guarded_Buzzer::set (int ms)
{
	Secure lock;
	Buzzer::set(ms);
}

void Guarded_Buzzer::sleep ()
{
	Secure lock;
	Buzzer::sleep();
}