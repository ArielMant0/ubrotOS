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
#include "meeting/bellringer.h"

#include "device/cgastr.h" // debugging

Watch g_watch(60);

void Watch::windup() {
	// Rgeister this handler as the plugbox
	g_plugbox.assign(g_plugbox.timer, *this);
	// Allow (timer) interrupts
	g_pic.allow(timer);
}

bool Watch::prologue() {
	g_pic.forbid(timer);

	return true;
}

void Watch::epilogue() {
	// Check bells
	g_bellringer.check();
	g_pic.allow(timer);
	g_scheduler.Scheduler::resume();
}
