/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "scheduler.h"

/* Hier muesst ihr selbst Code vervollstaendigen */ 
/* Hier muesst ihr selbst Code vervollstaendigen */ 

/*
 * Mit dieser Methode wird der Prozess that beim Scheduler angemeldet. 
 * Er wird an das Ende der Ready-Liste angefügt.
 */
void Scheduler::ready(Entrant& that)
{
	readyList.enqueue(that);
}

/*
 * Diese Methode setzt das Scheduling in Gang, indem der erste Prozess 
 * von der Ready-Liste entfernt und aktiviert wird.
 */
void Scheduler::schedule()
{
	Chain* tmp = readyList.dequeue();
	dispatch((Entrant*)tmp);
	//((Entrant*)tmp)->resume(); // TODO das hier ist schon im dispatch drin
}

/*
 * Hiermit kann sich ein Prozess selbst beenden. 
 * Er wird nun nicht wieder an das Ende der Ready-Liste angefügt. 
 * Statt dessen wird nur der erste Prozess von der Ready-Liste heruntergenommen und aktiviert. 
 */
void Scheduler::exit()
{
	// TODO was ist hier der unterschied zu schedule?
	Chain* tmp = readyList.dequeue();
	dispatch((Entrant*)tmp);
	//((Entrant*)tmp)->resume(); // TODO das hier ist schon im dispatch drin
}

/*
 * Mit dieser Methode kann ein Prozess einen anderen (that) beenden. 
 * Der Prozess that wird einfach von der Ready-Liste entfernt und 
 * erhält somit nie wieder den Prozessor.
 */
void Scheduler::kill(Entrant& that)
{
	readyList.remove(that);
}

/**
 * Hiermit kann ein Prozesswechsel ausgelöst werden, ohne dass der aufrufende Entrant wissen muss, 
 * welche anderen Entrant Objekte im System existieren und welcher davon sinnvollerweise aktiviert 
 * werden sollte. Diese Entscheidung trifft der Scheduler anhand der Einträge seiner Ready-Liste. 
 * Im derzeitigen System soll er den gerade laufenden Prozess an das Ende der Ready-Liste anfügen 
 * und den ersten aktivieren.
 */
void Scheduler::resume()
{
	// Füge laufenden hinzu
	readyList.enqueue(active());

	// Entferne ersten und führe aus
	Chain* tmp = readyList.dequeue();
	((Entrant*)tmp)->resume(); // TODO soll das hier go sein?
}