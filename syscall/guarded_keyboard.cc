/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ K E Y B O A R D                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zur Tastatur.                                   */
/*****************************************************************************/

#include "guarded_keyboard.h"
#include "guard/secure.h"

Guarded_Keyboard g_keyboard;

Key Guarded_Keyboard::getKey()
{
	Secure lock;
	return Keyboard::getKey();
}
