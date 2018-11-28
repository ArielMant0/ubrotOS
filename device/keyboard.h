/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "machine/keyctrl.h"
#include "guard/gate.h"
#include "machine/key.h"

class Keyboard : public Gate, public Keyboard_Controller
{
        
private:

	enum leds { caps_lock = 4, num_lock = 2, scroll_lock = 1 };

	bool m_num, m_scroll, m_caps;

    Keyboard (const Keyboard &copy); // Verhindere Kopieren

    bool specialStuff(Key &key);

    void checkInvalidKeys(Key &key);

public:

	Keyboard();
 
    // PLUGIN: 'Anstoepseln' der Tastatur. Ab sofort werden Tasten erkannt.
    void plugin ();

	void trigger() override;
};

extern Keyboard g_keyboard;

#endif
