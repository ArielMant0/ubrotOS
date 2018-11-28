/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#include "device/keyboard.h"
#include "machine/pic.h"
#include "machine/plugbox.h"

#include "device/cgastr.h"

Keyboard g_keyboard;

Keyboard::Keyboard()
{
	plugin();
}

void Keyboard::plugin()
{
	g_plugbox.assign(g_plugbox.keyboard, *this);
	g_pic.allow(keyboard);
}

void Keyboard::trigger()
{
	// Get Key
	Key key = key_hit();
	// Print key to screen
	if (key.valid()) 
	{
		if (!specialStuff(key)) 
		{
			kout << key.ascii();
			kout.flush();
		}
	}
	else
	{
		checkInvalidKeys(key);
	}
}

void Keyboard::checkInvalidKeys(Key &key) 
{
	if (key.caps_lock())
	{
		set_led(3, true);
	}
}

bool Keyboard::specialStuff(Key &key)
{
	// aktuelles verhalten:
	// wenn ich 1 ODER 2 drücke wird die erste Lampe aus und die zweite angemacht ...
	// das zurücksetzen der lampen geht komplett nicht
	// repeatrate hat keinen einfluss

	switch (key.ascii())
	{
		case '+':
		{
			set_repeat_rate(m_repeat_speed+1, m_repeat_delay);
			return true;
		}
		case '-':
		{
			set_repeat_rate(m_repeat_speed-1, m_repeat_delay);
			return true;
		}
		case '1':
		{
			set_led(1, true);
			break;
		}
		case '2':
		{
			set_led(2, true);
			break;
		}
		case '3':
		{
			set_led(4, true);
			break;
		}
		case '4':
		{
			set_led(1, false);
			break;
		}
		case '5':
		{
			set_led(2, false);
			break;
		}
		case '6':
		{
			set_led(4, false);
			break;
		}
		default:
		{
			if (key.scancode() == Key::scan::del && key.alt_left() && key.ctrl_left())
			{
				reboot();
				return true;
			}
		}
	}

	return false;
}

