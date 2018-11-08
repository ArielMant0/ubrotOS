/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ IO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#include "object/o_stream.h"

void O_Stream::flush()
{
	m_pos = 0;
}

void O_Stream::set_mode(O_Stream::Mode m)
{
	m_mode = m;
}

O_Stream& O_Stream::operator<<(unsigned char c)
{
	putc(c);
	return *this;
}

O_Stream& O_Stream::operator<<(char c)
{
	putc(c);
	return *this;
}

O_Stream& O_Stream::operator<<(unsigned short number)
{
	return operator<<((unsigned long)number);
}

O_Stream& O_Stream::operator<<(short number)
{
	return operator<<((long)number);
}

O_Stream& O_Stream::operator<<(unsigned int number)
{
	return operator<<((unsigned long)number);
}

O_Stream& O_Stream::operator<<(int number)
{
	return operator<<((long)number);
}

O_Stream& O_Stream::operator<<(unsigned long number)
{
	char tmp[32];
	short length = 0;

	for (short i = 0; number > 0; ++i, ++length)
	{
		number = number / 10;
		tmp[i] = (number % 10); // wrong way around
	}

	for (short i = 1; i <= length; ++i)
	{
		putc(tmp[length-i]); // right way around
	}

	return *this;
}

O_Stream& O_Stream::operator<<(long number)
{
  	if (number < 0)
	{
		putc('-');
		number *= -1;
	}
    return operator<<((unsigned long)number); 
}

O_Stream& O_Stream::operator<<(O_Stream& (*fkt) (O_Stream&))
{
	return fkt(*this);
}

char O_Stream::get_buffer_at(unsigned int i)
{
	return m_buffer[i];
}

O_Stream& endl (O_Stream& os)
{
	os.putc('\n');
	os.flush();
	return os;
}

O_Stream& bin (O_Stream& os)
{
	os.set_mode(O_Stream::Mode::BIN);
	return os;
}

O_Stream& oct (O_Stream& os)
{
	os.set_mode(O_Stream::Mode::OCT);
	return os;
}

O_Stream& dec (O_Stream& os)
{
	os.set_mode(O_Stream::Mode::DEC);
	return os;
}

O_Stream& hex (O_Stream& os)
{
	os.set_mode(O_Stream::Mode::HEX);
	return os;
}
