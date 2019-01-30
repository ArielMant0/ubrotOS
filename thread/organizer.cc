/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Organizer ist ein spezieller Scheduler, der zusaetzlich das Warten    */
/* von Threads (Customer) auf Ereignisse erlaubt.                            */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */ 

#include "organizer.h"

void Organizer::block (Customer& customer, Waitingroom& waitingroom)
{
	customer.waiting_in(&waitingroom);
	exit(); // resume() ?
}

void Organizer::wakeup (Customer& customer)
{
    customer.waiting_in(nullptr);
	ready(customer);
}

void Organizer::kill (Customer& that)
{
    if (that.waiting_in() == nullptr)
    {
        Scheduler::kill(that);
    }
    else
    {
        that.waiting_in()->remove(&that);
        that.waiting_in(nullptr);
	}
}