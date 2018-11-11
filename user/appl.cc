/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "device/cgastr.h"
         
/* GLOBALE VARIABLEN */

extern CGA_Stream kout;

const char TEST_RESULT[] = { 's', '1', 'g', '-', '4', '8', '7', '\n' };

bool Application::test_cga_screen()
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

bool Application::test_o_stream()
{
    O_Stream os;

    os << 's' << 1 << 'g' << -487 << '\n';

    for (int i = 0; i < 8; ++i)
    {
        if (os.get_buffer_at(i) != TEST_RESULT[i])
        {
            return false;
        }
    }

    return true;    
}

bool Application::test_cga_stream()
{
    kout << 's' << 1 << 'g' << -487 << '\n';

    for (int i = 0; i < 8; ++i)
    {
        if (kout.get_buffer_at(i) != TEST_RESULT[i])
        {
            return false;
        }
    }

    kout.flush();

    return true;    
}
         
void Application::action () {}

bool Application::test()
{
    bool screen = test_cga_screen();
    bool ostream = test_o_stream();
    bool cgastream = test_cga_stream();
    return screen && ostream && cgastream;
}
