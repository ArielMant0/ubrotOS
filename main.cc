/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "user/appl.h"
#include "thread/scheduler.h"
#include "device/cgastr.h"

static long stack[256];

int main()
{
    Application app((void*)(stack + sizeof (stack)));

    g_scheduler.ready(app);
	g_scheduler.schedule();

   	return 0;
}
