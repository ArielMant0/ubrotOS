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

#include "thread/scheduler.h"
#include "user/loop.h"

#include "machine/cpu.h" // TODO

void Application::action()
{
    {
        Secure lock;
        g_cga.clear();
    }
    
    g_cpu.enable_int();

    // Mache neue globale stacks und übergebe die loops dem scheduler
    static long stack1[256];
    Loop p1((void*)(stack1 + sizeof (stack1)), 75, 0);
    g_scheduler.ready(p1);

    // Mache neue globale stacks und übergebe die loops dem scheduler
    static long stack2[256];
    Loop p2((void*)(stack2 + sizeof (stack2)), 0, 0);
    g_scheduler.ready(p2);


    int x, y, counter = 0;
    while (true)
    {
        // beende p2
        if (counter++ == 1000) 
        {
            g_scheduler.kill(p2);
        }
        
        // Verwende lock aus einer der vorherigen Aufgaben
        {
            Secure lock;

            g_cga.getpos(x,y);
            g_cga.setpos(0,10);
            kout << "Counter in Appl " << counter << endl;

            g_cga.setpos(x,y);
        }

        g_scheduler.resume();
    };

    g_scheduler.exit();

}