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
    
    //int count = 0;
    //int x,y;
    g_cga.show(50, 5, 'A');
    
    kout << "endl" << endl;

    g_cpu.enable_int();
    /*
    while(true)
    {
        {
            Secure lock;
            g_cga.getpos(x,y);
            g_cga.setpos(75,0);
            kout << count++;
            if (count == 100000) {
                count = 0;
            }
            kout.flush();
            g_cga.setpos(x,y);
        }
    }*/
    kout << "endl" << endl;

    // andere Prozesse go!
    static long stack1[256];
    Loop p1((void*)(stack1 + sizeof (stack1)));
    // gebe dem scheduler den thread
    g_scheduler.ready(p1);

    static long stack2[256];
    Loop p2((void*)(stack2 + sizeof (stack2)));
    // gebe dem scheduler den thread
    g_scheduler.ready(p2);

    kout << "endl" << endl;

    int counter = 0;
    while (true) {
        
        // Wenn counter den Wert erreicht, beende Loop2
        counter++;
        if (counter == 1000) {
            g_scheduler.kill(p2);
        }
        
        // Ausgabe von Main mit Counter
        {
            Secure secure;
            kout << "Main - Counter: " << counter;
            kout.flush();
        }

        g_scheduler.resume();
    };

    g_scheduler.exit();

}