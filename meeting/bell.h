/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 B E L L                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Eine "Glocke" ist eine abstrakte Basisklasse, die das Ausloesen einer     */
/* Aktivitaet nach einer bestimmten Wartezeit erlaubt.                       */
/* Dazu besitzt sie einen Zaehler, der vom "Gloeckner" (Bellringer) ver-     */
/* waltet wird.                                                              */
/*****************************************************************************/

#ifndef __Bell_include__
#define __Bell_include__

#include "object/chain.h"

class Bell : public Chain
{
private:

	int m_count;

    Bell(const Bell &copy); // Verhindere Kopieren

public:

    Bell() : Chain() {}

	void wait (int value)
	{
		m_count = value;
	}

    // Setzen bzw. Abfragen des Zählers.
    int wait ()
    {
		return m_count;
    }

	// Dekremementiert den Zähler.
	void tick ()
	{
		m_count--;
	}

	// Liefert true, wenn die Zeit abgelaufen ist.
	bool run_down()
	{
		return m_count <= 0;
	}

	// Wird vom Glöckner aufgerufen, wenn es an der Zeit ist.
	virtual void ring () = 0;

};

#endif
