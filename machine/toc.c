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
	void **stack = &tos;
	*(stack--) = kickoff;
	*(stack) = object;
	toc_go(regs);
}


