/* $Id: toc.c 9719 2018-12-05 09:57:29Z df $ */

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 T O C                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Struktur toc dient dazu, bei einem Koroutinenwechsel die Werte der    */
/* nicht-fluechtigen Register zu sichern. toc_settle bereitet sie            */
/* entsprechend vor.                                                         */
/*****************************************************************************/

#include "machine/toc.h"

// TOC_SETTLE: bereitet den Kontext der Koroutine fuer den ersten
//             Aufruf vor.

void toc_settle(
	struct toc *regs,
	void *tos,
	void (*kickoff)(void*, void*, void*, void*, void*, void*, void*),
	void *object
) 
{
	// initialisiere die Elemente mit 0
	regs->rbx = 0;
	regs->r12 = 0;
	regs->r13 = 0;
	regs->r14 = 0;
	regs->r15 = 0;

	void **stack = tos; // pointer auf stack
	*(stack-1) = kickoff;
	*(stack-2) = object;

	regs->rbp = *(stack-2);
	regs->rsp = *(stack-1);
}


