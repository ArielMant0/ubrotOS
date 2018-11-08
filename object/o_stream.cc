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

void flush()
{
	
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
	while (number > 0)
	{
		number = number / 10;
		putc(number % 10); // wrong way around
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
