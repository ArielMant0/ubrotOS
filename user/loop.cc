/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop ist ein Thread, der nichts weiter tut als einen Zaehler hochzu-      */
/* zaehlen und dies auf dem Bildschirm anzuzeigen. Zwischendurch gibt er     */
/* den Prozessor ab. Der Scheduler bestimmt dann, welcher Thread als         */
/* naechstes laufen soll.                                                    */
/*****************************************************************************/

#include "user/loop.h" 

#include "device/cgastr.h"
#include "guard/secure.h"
#include "syscall/guarded_scheduler.h"
 
void Loop::action()
{
    for (int count = 1; count <= 200000; count++)
    {
        printGreeting(count);
        // Wait a bit
        for (int i = 0; i < 500; ++i) {}

        g_scheduler.resume();
    }

    g_scheduler.exit();
}

void Loop::printGreeting(int count)
{
    Secure lock;

    int x,y;

    g_cga.getpos(x,y);
    g_cga.setpos(m_x,m_y);
    kout << "[ Thread " << m_id << "] (" << count << '/' << 200000 << ')' << endl;
    g_cga.setpos(x,y);
}