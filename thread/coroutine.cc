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
#include "device/cgastr.h"


// Funktionen, die auf der C- oder Assembler-Ebene implementiert werden,
// muessen als extern "C" deklariert werden, da sie nicht dem Name-Mangeling
// von C++ entsprechen.
extern "C"
{
 	void toc_go(struct toc* regs);
	void toc_switch(struct toc* regs_now, struct toc* reg_then);
	void toc_settle(
		struct toc*, void*, 
		void (*func)(void*, void*, void*, void*, void*, void*, void*), 
		void*
	);
}

extern void kickoff(void*, void*, void*, void*, void*, void*, void*);

/**
 * Konstruktor
 */
Coroutine::Coroutine(void *tos)
{
	m_toc = toc();

	// Init den Stack
	toc_settle(&m_toc, tos, kickoff, this);
}

void Coroutine::go()
{
	// übergebe Pointer auf die Adresse des tocs
	// mit extern c angesprochen
	toc_go(&m_toc);
}

void Coroutine::resume(Coroutine &next)
{
	// Tausche den Inhalt der Register
	toc_switch(&m_toc, &(next.m_toc));
}