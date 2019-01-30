/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Liste von Threads, die auf ein Ereignis warten.                           */
/*****************************************************************************/

#include "waitingroom.h"
#include "syscall/guarded_organizer.h"
#include "thread/customer.h"

extern Guarded_Organizer g_organizer;

Waitingroom::~Waitingroom()
{
	// Gehe alle elem durch + wakeup
	for (Customer* elem = (Customer*)dequeue(); elem; elem = (Customer*)dequeue()) 
	{
		g_organizer.wakeup(*elem);
	}
}

void Waitingroom::remove(Customer* customer)
{
	Queue::remove(customer);
}