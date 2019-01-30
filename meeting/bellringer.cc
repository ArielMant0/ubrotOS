/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Der "Gloeckner" wird im Rahmen der Timer-Epilog Bearbeitung aktiviert.    */
/* Er prueft, ob irgendwelche Glocken (Bell-Objekte) laeuten muessen. Die    */
/* Glocken befinden sich in einer Queue, die der Gloeckner verwaltet.        */
/*****************************************************************************/

#include "bellringer.h"

Bellringer g_bellringer;

void Bellringer::check ()
{
	for (Bell *bell = (Bell*) first(); bell; bell=(Bell*)bell->next)
	{
		bell->tick();
		if (bell->run_down())
		{
			bell->ring();
		}
	}
}

void Bellringer::job (Bell *bell, int ticks)
{
	// TODO: sort after ticks
	bell->wait(ticks);
	enqueue(bell);
}

void Bellringer::cancel (Bell *bell)
{
	remove(bell);
}