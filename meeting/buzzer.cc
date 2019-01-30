/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe des "Weckers" koennen Prozesse eine bestimmte Zeit lang         */
/* schlafen und sich dann wecken lassen.                                     */
/*****************************************************************************/

#include "meeting/buzzer.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_organizer.h"

Buzzer::~Buzzer()
{
	g_bellringer.cancel(this);
	ring();
}

void Buzzer::ring()
{
	// Gehe alle elem durch + wakeup
	for (Customer* elem = (Customer*)dequeue(); elem; elem = (Customer*)dequeue()) 
	{
		g_organizer.wakeup(*elem);
	}
}

void Buzzer::set (int ms)
{
	g_bellringer.cancel(this);
	g_bellringer.job(this, ms);
}

void Buzzer::sleep()
{
	if (wait() > 0)
	{
    	Customer* customer = (Customer*) g_organizer.active();
    	if (customer)
    	{
    		enqueue(customer);
    		g_organizer.block(*customer, *this);
    	}
	}
}
