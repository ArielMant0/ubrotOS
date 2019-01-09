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
    int x,y;
    for (int count = 0; count < 100000; count++)
    {
        printGreeting();
        // Wait a bit
        for (int i = 0; i < 500; ++i) {}

        g_scheduler.resume();
    }

    g_scheduler.exit();
}

void Loop::printGreeting()
{
    Secure lock;

    kout << "[ Thread " << m_id << " says hello! ]" << endl;
}