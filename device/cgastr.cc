/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C G A _ S T R E A M                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse CGA_Stream ermoeglicht die Ausgabe verschiedener Datentypen    */
/* als Zeichenketten auf dem CGA Bildschirm eines PCs.                       */
/* Fuer weitergehende Formatierung oder spezielle Effekte stehen die         */
/* Methoden der Klasse CGA_Screen zur Verfuegung.                            */
/*****************************************************************************/

#include "device/cgastr.h"

CGA_Stream kout;

CGA_Stream::CGA_Stream() : O_Stream() {}

void CGA_Stream::flush()
{
    g_cga.print(m_buffer, m_pos);   
    O_Stream::flush();
}

CGA_Screen& CGA_Stream::screen()
{
	return g_cga;
}