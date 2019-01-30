/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe des "Weckers" koennen Prozesse eine bestimmte Zeit lang         */
/* schlafen und sich dann wecken lassen.                                     */
/*****************************************************************************/

#ifndef __Buzzer_include__
#define __Buzzer_include__

#include "meeting/bell.h"
#include "meeting/waitingroom.h"

class Buzzer : public Waitingroom, Bell
{

private:

    Buzzer(const Buzzer &copy); // Verhindere Kopieren

public:

	Buzzer() : Waitingroom(), Bell() {}

	virtual ~Buzzer();

	virtual void ring() override;

	void set (int ms);

	void sleep();
};

#endif
