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
	m_interval = 1193182 / frequency(us);
	// Write which counter to use
	m_control.outb(
		PIT::Counter::first << 6 | 
		PIT::ReadWrite::lowhigh << 4 | 
		PIT::Mode::periodic << 1 |
		PIT::Format::binary
	);
	// Set low byte
	m_count1.outb(m_interval & 0xFF); // unneccessary?
	// Set high byte
	m_count1.outb(m_interval >> 8);
}
