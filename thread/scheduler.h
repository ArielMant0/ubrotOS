/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/

#ifndef __schedule_include__
#define __schedule_include__

#include "thread/dispatch.h"
/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "object/queue.h"
#include "thread/entrant.h"

class Scheduler 
/* Hier muesst ihr selbst Code vervollstaendigen */         
{
private:
    Scheduler(const Scheduler &copy); // Verhindere Kopieren
/* Hier muesst ihr selbst Code vervollstaendigen */ 
    Queue readyList;

public:
	void ready(Entrant& that);
	
	void schedule();

 	void exit();

 	void kill(Entrant& that);

 	void resume();
};

#endif
