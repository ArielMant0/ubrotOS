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

Keyboard::Keyboard() : m_num(false), m_scroll(false), m_caps(false)
{
	set_led(leds::caps_lock, m_caps);
	set_led(leds::scroll_lock, m_scroll);
	set_led(leds::num_lock, m_num);
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
		m_caps = !m_caps;
		set_led(leds::caps_lock, m_caps);
	}
	else if (key.num_lock())
	{
		m_num = !m_num;
		set_led(leds::num_lock, m_num);
	}
	else if (key.scroll_lock())
	{
		m_scroll = !m_scroll;
		set_led(leds::scroll_lock, m_scroll);
	}
}

bool Keyboard::specialStuff(Key &key)
{
	switch (key.ascii())
	{
		case '+':
		{
			set_repeat_rate(m_repeat_speed+5, m_repeat_delay);
			return true;
		}
		case '-':
		{
			set_repeat_rate(m_repeat_speed-5, m_repeat_delay);
			return true;
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

