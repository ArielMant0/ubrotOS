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
#include "device/cgastr.h"
#include "machine/cpu.h"
#include "syscall/guarded_organizer.h"

extern Guarded_Semaphore screen_lock;

class IdleThread : public Application
{

private:

    IdleThread (const Application &copy); // Verhindere Kopieren

public:

    IdleThread(void *tos) : Application(tos) {}

    void action () override
    {
        int counter = 0;
        int x,y;
    	while (true)
        {
            screen_lock.wait();
            kout.getpos(x,y);
            kout.setpos(0,15);
            kout << "Idle Thread is running ... " << counter++ << endl;
            kout.setpos(x,y);
            screen_lock.signal();

            g_cpu.idle();
            g_organizer.resume();
        }
    }

    bool is_idle() override
    {
        return true;
    }

};

#endif