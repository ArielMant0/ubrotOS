/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          D I S P A T C H E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Dispatcher.                                           */
/* Der Dispatcher verwaltet den life-Pointer, der die jeweils aktive         */
/* Koroutine angibt. mit go() wird der life Pointer initialisiert und die    */
/* erste Koroutine gestartet, alle weiteren Kontextwechsel werden mit        */
/* dispatch() ausgeloest. active() liefert den life Pointer zurueck.         */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "thread/dispatch.h"

// Der Konstruktor initialisiert den Life-Pointer mit Null, um anzuzeigen, 
// dass noch keine Koroutine bekannt ist.
Dispatcher::Dispatcher()
{
    lifePointer = nullptr;
}

// Mit dieser Methode wird die Koroutine first im Life-Pointer vermerkt und gestartet.
void Dispatcher::go(Coroutine& first)
{
	// Wenn nullptr
	if(!lifePointer)
	{
    	lifePointer = &first;
    	lifePointer->go();
	}
}

// Diese Methode setzt den Life-Pointer auf next und führt einen Koroutinenwechsel 
// vom alten zum neuen Life-Pointer durch.
void Dispatcher::dispatch(Coroutine& next)
{
	Coroutine* now = lifePointer;

	lifePointer = &next;
	// TODO soll das hier go sein?
	now->resume(next);
}
 
// Hiermit kann abgefragt werden, welche Koroutine gerade im Besitz des Prozessors ist.    
Coroutine* Dispatcher::active()
{
    return lifePointer;
}
