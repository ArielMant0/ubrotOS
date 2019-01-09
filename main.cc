/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "user/appl.h"
#include "thread/scheduler.h"
#include "device/cgastr.h"

static long stack[256];

int main()
{
	// Erzeuge ersten thread mit stack
	// Appl ruft Entrant-Konstruktor auf und dann Coroutine-Konstruktor
    Application app((void*)(stack + (sizeof (stack) / 8)));

    // Füge den ersten Entrant ein
    g_scheduler.ready(app);
    // Organisiere die Entrants
	g_scheduler.schedule();

   	return 0;
}
