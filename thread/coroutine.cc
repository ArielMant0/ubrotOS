/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          C O R O U T I N E                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Koroutinenkonzepts.                                   */
/* Im Konstruktor wird der initiale Kontext der Koroutine eingerichtet.      */
/* Mit go() wird die erste Koroutine aktiviert. Alle weiteren Koroutinen-    */
/* wechsel sollten mit resume() erfolgen.                                    */
/* Um bei einem Koroutinenwechsel den Kontext sichern zu koennen, enthaelt   */
/* jedes Koroutinenobjekt eine Struktur toc, in dem die Werte der nicht-     */
/* fluechtigen Register gesichert werden koennen.                            */
/*****************************************************************************/

#include "thread/coroutine.h"
#include "machine/toc.c"

// Funktionen, die auf der C- oder Assembler-Ebene implementiert werden,
// muessen als extern "C" deklariert werden, da sie nicht dem Name-Mangeling
// von C++ entsprechen.
extern "C"
{
	Coroutine::Coroutine(void *tos)
	{
		m_toc = toc();
		// let stack pointer point to tos
		toc_settle((void*)&m_toc, tos, kickoff); // kickoff ?
	}

	/* Hier muesst ihr selbst Code vervollstaendigen */
	void Coroutine::resume(Coroutine &next)
	{
		// coroutine-switch
		toc_switch(m_toc, next.m_toc);
	}
}

void Coroutine::go()
{
	// ?
}
