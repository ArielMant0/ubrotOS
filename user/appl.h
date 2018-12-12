/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

#ifndef __application_include__
#define __application_include__

#include "thread/coroutine.h"

class Application : public Coroutine
{

private:

    Application (const Application &copy); // Verhindere Kopieren

    bool test_cga_screen();
    bool test_o_stream();
    bool test_cga_stream();
    bool test_keyboard();

public:
          
    Application(void *tos) : Coroutine(tos) {}

    void action () override;

    bool test();

};

#endif
