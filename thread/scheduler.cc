/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/

#include "scheduler.h"
#include "customer.h"
#include "user/idle.h"

//IdleThread idle;

/*
 * Mit dieser Methode wird der Prozess that beim Scheduler angemeldet. 
 * Er wird an das Ende der Ready-Liste angefügt.
 */
void Scheduler::ready(Entrant& that)
{
	readyList.enqueue(&that);
}

/*
 * Diese Methode setzt das Scheduling in Gang, indem der erste Prozess 
 * von der Ready-Liste entfernt und aktiviert wird.
 */
void Scheduler::schedule()
{
	// Frage den dispatcher ob nullptr vorliegt
	if (!active()) 
	{
		Entrant* tmp = (Entrant*)readyList.dequeue();
		if (tmp) 
		{
			go(*tmp);
		}
	}
}

/*
 * Hiermit kann sich ein Prozess selbst beenden. 
 * Er wird nun nicht wieder an das Ende der Ready-Liste angefügt. 
 * Statt dessen wird nur der erste Prozess von der Ready-Liste heruntergenommen und aktiviert. 
 */
void Scheduler::exit()
{
	// TODO: how to idle
	Entrant *tmp = (Entrant*)readyList.dequeue();
	if (tmp)// && tmp != (Entrant*) &idle)
	{
		dispatch(*tmp);
		return;
	}

	// TODO: Falls gerade alle Prozesse blockiert sind, muss mit einer geeigneten Methode
	//       gewartet werden, bis einer lauffähig wird
	/*while (true)
	{
		for (Entrant *e = (Entrant*)tmp->next; e; e = (Entrant*)e->next)
		{
			c = (Customer*) e;
			if (c->waiting_in() == nullptr)
			{
				readyList.remove(e);
				dispatch(*e);
				return;
			}
		}
	}*/
}

/*
 * Mit dieser Methode kann ein Prozess einen anderen (that) beenden. 
 * Der Prozess that wird einfach von der Ready-Liste entfernt und 
 * erhält somit nie wieder den Prozessor.
 */
void Scheduler::kill(Entrant& that)
{
	// Stelle sicher das es nicht der aktive ist
	if (active() != &that) 
	{
		readyList.remove(&that);
	} 
	else 
	{
		exit();
	}
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
	// Entferne ersten und führe aus
	// wenn es nur einen gibt wird der alte erneut ausgeführt
	Entrant* tmp = (Entrant*)readyList.dequeue();
	if (tmp) {
		// Füge laufenden hinzu
		readyList.enqueue((Entrant*)active());

		dispatch(*tmp);
	}
}