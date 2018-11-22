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
	if (key.valid()) {
		if (!specialStuff(key)) {
			kout << key.ascii();
			kout.flush();
		}
	}
}

bool Keyboard::specialStuff(Key &key) {
	switch (key.ascii())
	{
		case '+':
		{
			//set_repeat_rate();
			kout << "+a" << endl;
			return true;
		}
		case '-':
		{
			kout << "-a" << endl;
			return true;
		}
		case '':
			
	}

	return false;
}