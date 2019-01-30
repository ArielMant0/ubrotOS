/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ O R G A N I Z E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Organizer.                                  */
/*****************************************************************************/

#include "guarded_organizer.h"
#include "guard/secure.h"

Guarded_Organizer g_organizer;

void Guarded_Organizer::ready(Thread& that)
{
	Secure lock;
	Organizer::ready(that);
}

void Guarded_Organizer::exit()
{
	Secure lock;
	Organizer::exit();
}

void Guarded_Organizer::kill(Thread& that)
{
	Secure lock;
	Organizer::kill(that);
}

void Guarded_Organizer::resume()
{
	Secure lock;
	Organizer::resume();
}