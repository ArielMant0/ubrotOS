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
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_buzzer.h"

void Loop::action()
{
    for (int count = 1; count <= m_iter; count++)
    {
        printGreeting(count);

        g_organizer.resume();
    }

    g_organizer.exit();
}

void Loop::printGreeting(int count)
{
    // Secure s;
    int x,y;

    screen_lock.wait();
    kout.getpos(x,y);
    kout.setpos(m_x,m_y);
    kout << "[ Thread " << m_id << "] (" << count << '/' << m_iter << ')' << endl;
    kout.setpos(x,y);
    screen_lock.signal();

    if (count > m_iter/2)
    {
        Guarded_Buzzer buzzer;
        buzzer.set(100);
        buzzer.sleep();
    }
}