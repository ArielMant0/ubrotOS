/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "user/appl.h"
#include "user/idle.h"
#include "syscall/guarded_organizer.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "machine/cpu.h"

#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "machine/pic.h"

static long stack[256];

static long idleStack[256];
IdleThread idle((void*)(idleStack + (sizeof (idleStack) / 8)));

int main()
{
	Secure lock; // !
	// Erzeuge ersten thread mit stack
	// Appl ruft Entrant-Konstruktor auf und dann Coroutine-Konstruktor
    Application app((void*)(stack + (sizeof (stack) / 8)));
    // Füge den ersten Entrant ein
    g_organizer.Scheduler::ready(app);
	// Enable interrupts
    g_cpu.enable_int();
    // Set the timer
	g_watch.windup();
	// Organisiere die Entrants
	g_organizer.schedule();

   	return 0;
}
