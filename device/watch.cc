/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

#include "watch.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "syscall/guarded_scheduler.h"

#include "device/cgastr.h" // debugging

Watch g_watch(60000); // 60 ms

void Watch::windup() {
	// Rgeister this handler as the plugbox
	g_plugbox.assign(g_plugbox.timer, *this);
	// Allow (timer) interrupts
	g_pic.allow(g_plugbox.timer);
}

bool Watch::prologue() {
	g_pic.forbid(g_plugbox.timer);
	return true;
}

void Watch::epilogue() {
	int x,y;
	g_cga.getpos(x, y);
    g_cga.setpos(0, 11);
    kout << "Watch: Timer Interrupt (" << m_count++ << ')';
    kout.flush();
	g_cga.setpos(x, y);

	g_pic.allow(g_plugbox.timer);
	g_scheduler.Scheduler::resume();
}
