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

	Key m_key;

    Keyboard (const Keyboard &copy); // Verhindere Kopieren

    bool specialStuff(Key &key);

public:

	Keyboard();
 
    // PLUGIN: 'Anstoepseln' der Tastatur. Ab sofort werden Tasten erkannt.
    void plugin ();

	bool prologue() override;

	void epilogue() override;

};

extern Keyboard g_keyboard;

#endif
