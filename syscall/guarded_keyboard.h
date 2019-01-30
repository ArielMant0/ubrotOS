/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ K E Y B O A R D                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zur Tastatur.                                   */
/*****************************************************************************/

#ifndef __Guarded_Keyboard_include__
#define __Guarded_Keyboard_include__

#include "device/keyboard.h"
       
/**
 * Die Klasse Guarded_Keyboard stellt die Systemaufrufschnittstelle zur Tastatur zur Verfügung. 
 */ 
class Guarded_Keyboard : public Keyboard
{
private:
    Guarded_Keyboard(const Guarded_Keyboard &copy); // Verhindere Kopieren

public:
    Guarded_Keyboard() : Keyboard() {}

    /**
     * Diese Methode entspricht der gleichnamigen Methode der Basisklasse Keyboard, 
     * nur dass sie mit Hilfe eines Secure Objekts geschützt wird.
     */
	Key getKey() override;
};

extern Guarded_Keyboard g_keyboard;

#endif
