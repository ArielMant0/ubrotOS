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

CGA_Stream::CGA_Stream(CGA_Screen &cga) : O_Stream()
{
    *m_screen = cga;
}

void CGA_Stream::flush()
{
    for (int i = 0; i < m_pos; i++)
    {
        m_screen->print(m_buffer, m_pos);   
    }
    O_Stream::flush();
}
