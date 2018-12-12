/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "user/appl.h"

int stack[256];

int main()
{
    Application app((void*)stack); // TODO: where does stack start?

    app.action();

   	return 0;
}
