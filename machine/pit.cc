/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#include "pit.h"

void PIT::interval (int us) {
	m_interval = us;//1193182 / frequency(us);

	int cmd = PIT::Counter::first << 6 | 
		PIT::ReadWrite::lowhigh << 4 | 
		PIT::Mode::periodic << 1 |
	 	PIT::Format::binary;

	// Write which counter to use
	m_control.outb(cmd);

	// Set low byte
	m_count1.outb(m_interval & 0xff);
	// Set high byte
	m_count1.outb(m_interval >> 8);
}
