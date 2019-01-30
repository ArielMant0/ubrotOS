/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "device/cgastr.h"
#include "guard/secure.h"

#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "user/loop.h"

Guarded_Semaphore screen_lock(1);

void Application::action()
{
    screen_lock.wait();
    kout.clear();
    screen_lock.signal();

    // Mache neue globale stacks und übergebe die loops dem scheduler
    static long stack1[256];
    Loop p1((void*)(stack1 + (sizeof (stack1) / 8)), 1, 0, 9);
    g_organizer.ready(p1);

    // Mache neue globale stacks und übergebe die loops dem scheduler
    static long stack2[256];
    Loop p2((void*)(stack2 + (sizeof (stack2) / 8)), 2, 0, 11);
    g_organizer.ready(p2);

    int x, y, counter = 0;
    while (true)
    {
        Key the_key = g_keyboard.getKey();

        // beende p2
        if (counter++ == 75000) 
        {
            g_organizer.kill(p2);
            //Secure s;
            screen_lock.wait();

            kout.getpos(x,y);
            kout.setpos(0,6);
            kout << "    Killed Thread 2" << endl;
            kout.setpos(x,y);

            screen_lock.signal();
        }
        
        // Verwende lock aus einer der vorherigen Aufgaben
        screen_lock.wait();
        {
            //Secure s;
            kout.getpos(x,y);
            kout.setpos(0,5);
            kout << "  Main Application: " << counter << " (last key: ";// << endl;
            kout << the_key.ascii() << ')' << endl;
            kout.setpos(x,y);
        }
        screen_lock.signal();
        
        //g_organizer.resume();
    }
}