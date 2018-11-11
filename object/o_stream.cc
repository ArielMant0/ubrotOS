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
	calc_num(number);
	return *this;
}

O_Stream& O_Stream::operator<<(long number)
{
    calc_num(number);
	return *this; 
}

O_Stream& O_Stream::operator<<(O_Stream& (*fkt) (O_Stream&))
{
	return fkt(*this);
}

char O_Stream::get_buffer_at(unsigned int i)
{
	return m_buffer[i];
}

void O_Stream::calc_num(long number)
{
	char tmp[64];
	int length = 0;
	int divisor;

	if (number < 0) {
		number = (number ^ 1) + 1; // 2s complement
	}
	calc_num((unsigned long)number);
}

void O_Stream::calc_num(unsigned long number)
{
	char tmp[64];
	int length = 0;
	int divisor;

	switch (m_mode)
	{
		case Mode::BIN:
			divisor = 2; break;
		case Mode::HEX:
			// TODO: special case, do stuff here
			for (int i = 0; number > 0; ++i, ++length)
			{
				number = number / 16;
				long tmp = (number % 16);
				tmp[i] = tmp < 10 ? tmp : tmp; // wrong way around
			}
			break;
		case Mode::OCT:
			divisor = 8; break;
		case Mode::DEC:
			divisor = 10; break;
	}

	for (int i = 0; m_mode != Mode::HEX && number > 0; ++i, ++length)
	{
		number = number / divisor;
		tmp[i] = (number % divisor); // wrong way around
	}
	for (int i = 1; i <= length; ++i)
	{
		putc(tmp[length-i]); // right way around
	}
}

O_Stream& endl(O_Stream& os)
{
	os.putc('\n');
	os.flush();
	return os;
}

O_Stream& bin(O_Stream& os)
{
	os.set_mode(O_Stream::Mode::BIN);
	return os;
}

O_Stream& oct(O_Stream& os)
{
	os.set_mode(O_Stream::Mode::OCT);
	return os;
}

O_Stream& dec(O_Stream& os)
{
	os.set_mode(O_Stream::Mode::DEC);
	return os;
}

O_Stream& hex(O_Stream& os)
{
	os.set_mode(O_Stream::Mode::HEX);
	return os;
}
