/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/

#ifndef __clock_include__
#define __clock_include__

#include "guard/gate.h"

class Clock : public Gate {

private:

	Clock(const Clock &other); // no copying

	void addSecond();

	void addMinute();

	void addHour();

	int m_hours, m_minutes, m_seconds;

public:

	Clock();

	void printTime();

	void trigger() override;
};

extern Clock g_clock;

#endif