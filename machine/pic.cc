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

/* INCLUDES */

#include "machine/pic.h"
#include "machine/cpu.h"

#include "device/cgastr.h"

PIC g_pic;

PIC::PIC() : m_imr1(0x21), m_imr2(0xa1)
{
	// Set masks
	m_mask1 = m_imr1.inb();
	m_mask2 = m_imr2.inb();
}

void PIC::forbid(int interrupt_device)
{
	if (interrupt_device < 8) 
	{
		m_mask1 = m_mask1 | get_mask(interrupt_device);
		m_imr1.outb(m_mask1);
	} 
	else 
	{
		m_mask2 = m_mask2 | get_mask(interrupt_device);
		m_imr2.outb(m_mask2);
	}
}

void PIC::allow(int interrupt_device)
{
	if (interrupt_device < 8) 
	{
		m_mask1 = m_mask1 & (~get_mask(interrupt_device));
		m_imr1.outb(m_mask1);
	} 
	else 
	{
		m_mask2 = m_mask2 & (~get_mask(interrupt_device));
		m_imr2.outb(m_mask2);
	}
}

bool PIC::is_masked(int interrupt_device)
{
	if (interrupt_device < 8) 
	{
		return get_mask(interrupt_device) & m_mask2;
	} 
	else 
	{
		return get_mask(interrupt_device) & m_mask2;
	}
}