/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Semaphor.                                   */
/*****************************************************************************/

#include "guarded_semaphore.h"
#include "guard/secure.h"

void Guarded_Semaphore::p()
{
	Secure lock;
	Semaphore::p();
}
    
void Guarded_Semaphore::v()
{
	Secure lock;
    Semaphore::v();
}

void Guarded_Semaphore::wait()
{
	Secure lock;
    Semaphore::wait();
}

void Guarded_Semaphore::signal()
{
	Secure lock;	
    Semaphore::signal();
}
