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
#include "device/keyboard.h"

#include "machine/cpu.h" // TODO

/* GLOBALE VARIABLEN */

extern CGA_Stream kout; // TODO

const char TEST_RESULT1[] =
{
    "s1g-487\n"
};
const char TEST_RESULT2[] =
{
    "-1 487 -123459876 1"
};
const char TEST_RESULT3[] =
{
    "2 10 11101001 -23\n"
};
const char TEST_RESULT4[] =
{
    "8 10 351 -23\n"
};
const char TEST_RESULT5[] =
{
    "10 A E9 -23\n"
};

bool Application::test_cga_screen()
{
    CGA_Screen cga; // TODO

    // simple write
    kout << "Test simple write command at x=20 and y=10:" << endl;
    cga.show(40, 10, 'a');
    if (cga.get_char(40, 10) != 'a')
    {
    	cga.print_error("appl.cc", 7);
    	return false;
    }

    int x,y;
    // check cursor pos
    kout << "Check for cursor position:" << endl;

    cga.setpos(0, 10);
    cga.getpos(x, y);
    if (x != 0 || y != 10)
    {
    	cga.print_error("appl.cc", 7);
    	return false;
    }

    // newline in text
    kout << "Check for newlines in text:" << endl;

    cga.print("Simple test text\n", 17);
    cga.print("Simple test\ntext", 16);

    // wrap
    kout << "Check if cursor is wrapped:" << endl;

    cga.setpos(85, 15);
    cga.getpos(x, y);
    if (x != 0 || y != 16)
    {
        cga.print_error("appl.cc", 7);
     	return false;
    }

	// more newline in text
    kout << "Check for more newlines in text:" << endl;

    cga.print("Simple\n test text", 17);
    cga.print("Simple\ntest text\n", 17);

    // scrolling
    kout << "Check for scrolling function:" << endl;

    for (int count = 0; count < 0; ++count)
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

// TODO teste 0
    kout << 2 << ' ' << bin << 2 << ' ' << -23 << ' ' << dec << -23 << '\n';

    for (int i = 0; i < 18; ++i)
    {
        if (kout.get_buffer_at(i) != TEST_RESULT3[i])
        {
            cga.print_error("appl.cc", 7);
            return false;
        }
    }

    kout.flush();

    kout << 8 << ' ' << oct << 8 << ' ' << -23 << ' ' << dec << -23 << '\n';

    for (int i = 0; i < 13; ++i)
    {
        if (kout.get_buffer_at(i) != TEST_RESULT4[i])
        {
            cga.print_error("appl.cc", 7);
            return false;
        }
    }

    kout.flush();

    kout << 10 << ' ' << hex << 10 << ' ' << -23 << ' ' << dec << -23 << '\n';

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
    CGA_Screen &cga = g_cga;
    Keyboard_Controller keyboard;

    // capslock = 4, numlock = 2, scrolllock = 1
    for (int i = 0; false && i < 10000; ++i)
    {
        int tmp = i < 1000 ? i : i % 1000;
        if (tmp == 0)
            keyboard.set_led(4, true);
    }

    Key key;
    for(int i = 0;; ++i)
    {
        key = keyboard.key_hit();
        if (key.valid())
        {
            if (key.ascii() == '1')
            {
                cga.clear();
                kout.flush();
                test_cga_screen();
            }
            else if (key.ascii() == '2')
            {
                cga.clear();
                kout.flush();
                test_o_stream();
            }
            else if (key.ascii() == '3')
            {
                cga.clear();
                kout.flush();
                test_cga_stream();
            }
            else if (key.ascii() == '4')
            {
                cga.clear();
                kout.flush();

                for(int i = 0;; ++i)
                {
                    if (key.ascii() == '1' || key.ascii() == '2' || key.ascii() == '3')
                        break;

                    key.invalidate();
                    key = keyboard.key_hit();
                    if (key.valid())
                    {
                        kout << key.ascii();
                        kout.flush();
                    }
                }
            }
            key.invalidate();
        }
    }

    return true;
}


void Application::action()
{
    int count = 0;
    int x,y;

    g_cpu.enable_int();
    while(true)
    {
        g_cga.getpos(x,y);
        g_cga.setpos(75,0);
        kout << count++;
        kout.flush();
        g_cga.setpos(x,y);

        if (count >= 10000) {
            count = 0;
        }
    }
}

bool Application::test()
{
    kout << endl;
    return test_keyboard();
}
