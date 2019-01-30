/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "semaphore.h"
#include "syscall/guarded_organizer.h"

extern Guarded_Organizer g_organizer;

Semaphore::Semaphore(int c) 
{
	count = c;
}

void Semaphore::p() 
{
	if (count > 0) 
	{
		count--;
	}
	else
	{
		// reihe aktives Elem ein und blockiere es
        Customer* customer = (Customer*) g_organizer.active();
        if (customer)
        {
        	enqueue(customer);
			g_organizer.block(*customer, *this); // (Waitingroom) 
        }
	}
}

void Semaphore::v() 
{
	Customer* customer = (Customer*) dequeue();
	if (customer) 
	{
		g_organizer.wakeup(*customer);
	}
	else
	{
		count++;
	}
}

void Semaphore::wait() 
{
	p();
}

void Semaphore::signal() 
{
	v();
}