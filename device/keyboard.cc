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

// Keyboard g_keyboard;

Keyboard::Keyboard() : m_keySema(0), m_gotKey(true)
{
	plugin();
}

void Keyboard::plugin()
{
	g_plugbox.assign(g_plugbox.keyboard, *this);
	g_pic.allow(keyboard);
}

bool Keyboard::prologue()
{
	// Get Key
	m_key = key_hit();
	// If its a valid key, do the epilogue
	if (m_key.valid()) {
		g_pic.forbid(keyboard);
		return true;
	}
	return false;
}

void Keyboard::epilogue()
{
	// Print key to screen
	/*if (!specialStuff(m_key) && m_key.valid())
	{
		kout << m_key.ascii();
		kout.flush();
	}*/
	g_pic.allow(keyboard);

	// Singal that a key was read
	if (m_gotKey) {
        m_gotKey = false;
        m_keySema.signal();
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

Key Keyboard::getKey()
{
	m_keySema.wait();
    m_gotKey = true;
	return m_key;
}