/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Locker implementiert eine Sperrvariable, die verwendet wird,   */
/* um kritische Abschnitte zu schuetzen. Die Variable zeigt allerdings nur   */
/* an, ob der kritische Abschnitt frei ist. Ein eventuelles Warten und der   */
/* Schutz der fuer diese Klasse notwendigen Zaehlfunktion muss ausserhalb    */
/* erfolgen.                                                                 */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

#include "device/cgastr.h"
#include "machine/cpu.h"

class Locker
{
private:

	bool n_locked;

    Locker(const Locker &copy); // Verhindere Kopieren

public:

	Locker() : m_locked(false) {}

	void enter()
	{
		if (m_locked)
		{
			kout << "Lock already active" << endl;
			g_cpu.halt();
		}
		m_locked = true;
	}

	void retne()
	{
		if (!m_locked)
		{
			kout << "Lock already inactive" << endl;
			g_cpu.halt();
		}
		m_locked = false;
	}

	bool avail()
	{
		return m_locked;
	}
};

#endif
