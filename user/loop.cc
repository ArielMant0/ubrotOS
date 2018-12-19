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

 
void Loop::action()
{
    int count = 0;
    int x,y;

    while(true)
    {
        {
            Secure lock;
            g_cga.getpos(x,y);
            g_cga.setpos(75,0);
            kout << count++;
            if (count == 10000) {
                count = 0;
            }
            kout.flush();
            g_cga.setpos(x,y);
        }
    }
}