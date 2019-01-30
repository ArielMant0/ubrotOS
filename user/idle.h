/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

#ifndef __idlethread_include__
#define __idlethread_include__

#include "user/appl.h"

class IdleThread : public Application
{

private:

    IdleThread (const Application &copy); // Verhindere Kopieren

public:
          
    IdleThread() : Application(nullptr) {}

    void action () override
    {
    	// TODO
    }

};

#endif