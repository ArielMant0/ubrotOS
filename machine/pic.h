/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* Mit Hilfe des PICs koennen Hardware-Unterbrechungen einzeln zugelassen    */
/* oder unterdrueckt werden. Auf diese Weise wird also bestimmt, ob die      */
/* Unterbrechung eines Geraetes ueberhaupt an den Prozessor weitergegeben    */
/* wird. Selbst dann erfolgt eine Aktivierung der Unterbrechungsroutine nur, */
/* wenn der Prozessor bereit ist, auf Unterbrechungen zu reagieren. Dies     */
/* kann mit Hilfe der Klasse CPU festgelegt werden.                          */
/*****************************************************************************/

#ifndef __pic_include__
#define __pic_include__

/* INCLUDES */
#include "machine/io_port.h"


enum
{
    timer    = 0,
    keyboard = 1
};


class PIC
{

public:
    PIC();

	/**
 	 * Lässt zu, dass der PIC Unterbrechungen des Geräts Nummer 
 	 * interrupt_device an den Prozessor weiterleitet.
 	 */
	void allow(int interrupt_device);

	/**
	 * Verhindert, dass der PIC Unterbrechungen des Geräts Nummer 
	 * interrupt_device an den Prozessor weiterleitet.
	 */
	void forbid(int interrupt_device);

	/**
	 * Gibt den Zustand des Maskierbits von interrupt_device zurück. 
	 * Wenn Unterbrechungen dieses Geräts nicht an die CPU weitergeleitet werden, 
	 * soll true zurückgegeben werden, andernfalls false. 
	 */
	bool is_masked(int interrupt_device);

private:
	PIC(const PIC &copy); // Verhindere Kopieren

	int get_mask(int interrupt_device)
	{
		if (interrupt_device < 8) 
		{
			return 1 << interrupt_device;
		} 
		else 
		{
			return 1 << (interrupt_device-8);
		}
	}

	// Interrupt Mask Registers for PIC1 and PIC2
	IO_Port m_imr1, m_imr2;
	// Currently enabled ports for PIC1 and PIC2
	int m_mask1, m_mask2;

};

extern PIC g_pic;

#endif
