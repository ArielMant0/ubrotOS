/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Semaphor.                                   */
/*****************************************************************************/

#ifndef __Guarded_Semaphore_include__
#define __Guarded_Semaphore_include__

#include "meeting/semaphore.h"
        
class Guarded_Semaphore : public Semaphore
{
private:
    Guarded_Semaphore(const Guarded_Semaphore &copy); // Verhindere Kopieren

public:

	/**
     * Der Konstruktor reicht nur den Parameter c an den Konstruktor der Basisklasse weiter. 
     */	
	Guarded_Semaphore(int c) : Semaphore(c) {}

	/**
	 * siehe Semaphore::p()
	 */
	void p();
    
    /**
     * siehe Semaphore::v()
     */
	void v();

	/**
	 * siehe Semaphore::wait()
	 */
	void wait();
    
    /**
     * siehe Semaphore::signal()
     */
	void signal();
};

#endif
