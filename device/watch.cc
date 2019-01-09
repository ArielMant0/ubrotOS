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

Watch g_watch(20000); // 20 ms

void Watch::windup() {
	// Rgeister this handler as the plugbox
	g_plugbox.assign(g_plugbox.timer, *this);
	// Allow (timer) interrupts
	g_pic.allow(g_plugbox.timer);
}

bool Watch::prologue() {
	kout << "PROLOG" << endl;
	return true;
}

void Watch::epilogue() {
	kout << "hello" << endl;
	g_scheduler.resume();
}
