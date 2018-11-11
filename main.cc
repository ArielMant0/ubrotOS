/* $Id: main.cc 8485 2017-03-27 11:50:06Z friesel $ */

/* Hier muesst ihr selbst Code vervollstaendigen */ 

#include "machine/cgascr.h"
#include "device/cgastr.h"

void test_cga_screen(CGA_Screen &cga)
{
    // simple write
    cga.show(20, 0, 'a');
    if (cga.get_char(20, 0) != 'a')
    {
    	cga.show(10, 10, '!');
    	return;
    }
    else
    {
		cga.show(10, 10, '#');
    }

    int x,y;
    // check cursor pos
    cga.setpos(0, 10);
    cga.getpos(x, y);
    if (x != 0 || y != 10)
    {
    	cga.show(10, 10, '!');
    	return;
    }
    else
    {
		cga.show(10, 10, '#');
    }

    // newline in text
    cga.print("Hallo 1!\n", 9);
    cga.print("w\nw", 3);

    // wrap
    cga.setpos(85, 15);
    cga.getpos(x, y);
    if (x != 0 || y != 16)
    {
     	return;
    }

	// more newline in text
    cga.print("Hallo 3!\n wuhuw", 15);
    cga.print("Hallo 3!\nwuhuw\n", 15);

    // scrolling
    for (int count = 0;; ++count)
    {
    	switch ((count/400) % 4)
    	{
    		case 0:
    			cga.print("|\n", 2); break;
    		case 1:
    			cga.print("/\n", 2); break;
    		case 2:
    			cga.print("-\n", 2); break;
    		case 3:
    			cga.print("\\\n", 2); break;
    	}
    }
}

void test_ostream(CGA_Screen &cga)
{
    O_Stream os;

    os << 's' << 1 << 'g' << -487 << endl;

    for (int i = 0; i < 8; ++i)
    {
        cga.show(i, 10, os.get_buffer_at(i));
    }
}

void test_cga_stream(CGA_Screen &cga)
{
    CGA_Stream cgs(cga);

    cgs << 's' << 1 << 'g' << -487 << endl;
    cgs.flush();
}

int main()
{
    CGA_Screen cga;
	// test_cga_screen(cga);
    test_ostream(cga);
    test_cga_stream(cga);

   	return 0;
}
