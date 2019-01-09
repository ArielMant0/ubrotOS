/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "user/appl.h"
#include "syscall/guarded_scheduler.h"
#include "device/cgastr.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "machine/cpu.h"

static long stack[256];

int main()
{
	Secure lock; // !
	// Erzeuge ersten thread mit stack
	// Appl ruft Entrant-Konstruktor auf und dann Coroutine-Konstruktor
    Application app((void*)(stack + (sizeof (stack) / 8)));
    // Füge den ersten Entrant ein
    g_scheduler.Scheduler::ready(app);
	// Enable interrupts
    g_cpu.enable_int();
    // Set the timer
	g_watch.windup();
	kout << "Intervall is " << g_watch.interval() << endl;
	// Organisiere die Entrants
	g_scheduler.Scheduler::schedule();
   	
   	return 0;
}
