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
#include "machine/keyctrl.h"
         
/* GLOBALE VARIABLEN */

/*extern */CGA_Stream kout; // TODO

const char TEST_RESULT1[] = { 's', '1', 'g', '-', '4', '8', '7', '\n' };
const char TEST_RESULT2[] = 
{ 
    '-', '1', ' ', '4', '8', '7', ' ', '-',
    '1', '2', '3', '4', '5', '9', '8', '7', 
    '6', ' ', '1'
};
const char TEST_RESULT3[] = 
{ 
    '2', ' ', '1', '0', ' ', '1', '0', '1',
    '1', '1', ' ', '2', '3', '\n'
};
const char TEST_RESULT4[] = 
{ 
    '8', ' ', '1', '0', ' ', '2', '7', ' ',
    '2', '3', '\n'
};
const char TEST_RESULT5[] = 
{ 
    '1', '0', ' ', 'A', ' ', 'B', '1', ' ', '1',
    '7', '7', '\n'
};

bool Application::test_cga_screen()
{
    CGA_Screen cga; // TODO

    // simple write
    cga.show(20, 0, 'a');
    if (cga.get_char(20, 0) != 'a')
    {
    	cga.show(10, 10, '!');
    	return false;
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
    	return false;
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
     	return false;
    }

	// more newline in text
    cga.print("Hallo 3!\n wuhuw", 15);
    cga.print("Hallo 3!\nwuhuw\n", 15);

    // scrolling
    for (int count = 0; false; ++count)
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

    return true;
}

bool Application::test_o_stream()
{
    CGA_Screen cga; // TODO
    O_Stream os;

    os << 's' << 1 << 'g' << -487 << '\n'; // TODO wenn ich jetzt hier endl mache, soll das dann ausgegeben werden oder nicht ?

    for (int i = 0; i < 8; ++i)
    {
        if (os.get_buffer_at(i) != TEST_RESULT1[i])
        {
            cga.print_error("appl.cc", 7);
            return false;
        }
    }

    return true;    
}

bool Application::test_cga_stream()
{
    CGA_Screen cga;

    // test char, unsingned char, int und unsigned int und \n
    kout << 's' << 1 << 'g' << -487 << '\n';

    for (int i = 0; i < 8; ++i)
    {
        if (kout.get_buffer_at(i) != TEST_RESULT1[i])
        {
            cga.print_error("appl.cc", 7);
            return false;
        }
    }

    kout.flush();

    // test short, unsigned short, long und unsigned long und endl
    kout << (short)-1 << ' ' << (unsigned short)487 << ' ' << -123459876 << ' ' << (unsigned long) 1 << endl;

    for (int i = 0; i < 19; ++i)
    {
        if (kout.get_buffer_at(i) != TEST_RESULT2[i])
        {
            cga.print_error("appl.cc", 7);
            return false;
        }
    }

    kout << 2 << ' ' << bin << 2 << ' ' << 23 << ' ' << dec << 23 << '\n';

    for (int i = 0; i < 14; ++i)
    {
        if (kout.get_buffer_at(i) != TEST_RESULT3[i])
        {
            cga.print_error("appl.cc", 7);
            return false;
        }
    }

    kout.flush();

    kout << 8 << ' ' << oct << 8 << ' ' << 23 << ' ' << dec << 23 << '\n';

    for (int i = 0; i < 10; ++i)
    {
        if (kout.get_buffer_at(i) != TEST_RESULT4[i])
        {
            cga.print_error("appl.cc", 7);
            return false;
        }
    }

    kout.flush();

    kout << 10 << ' ' << hex << 10 << ' ' << 177 << ' ' << dec << 177 << '\n';

    for (int i = 0; i < 12; ++i)
    {
        if (kout.get_buffer_at(i) != TEST_RESULT5[i])
        {
            cga.print_error("appl.cc", 7);
            return false;
        }
    }

    kout.flush();

    return true;    
}
      
bool Application::test_keyboard() 
{
    Keyboard_Controller keyboard;

    // capslock = 4, numlock = 2, scrolllock = 1
    /*for (int i = 0; i < 10000; i++)
    {
        if (i % 1000 == 0)
            keyboard.set_led(4, true);
    }*/

    
    Key key;
    for(int i = 0;; ++i)
    {
        key = keyboard.key_hit();
        kout << i;
        kout.flush();
        if (key.valid())
        {
            kout << ' ' << key.ascii();
            kout.flush();
        }
    }

    return true;
}

void Application::action() 
{

}

bool Application::test()
{
    bool screen = true;//test_cga_screen();
    bool ostream = true;//test_o_stream();
    bool cgastream = true;//test_cga_stream();
    bool keyboard = test_keyboard();
    return screen && ostream && cgastream && keyboard;
}
