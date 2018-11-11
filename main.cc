/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

#include "user/appl.h"

int main()
{
    Application app;
    if (!app.test())
    {
        return -1;
    }

   	return 0;
}
