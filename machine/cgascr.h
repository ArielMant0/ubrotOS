#ifndef __screen_include__
#define __screen_include__

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse kann man auf den Bildschirm des PCs zugreifen.    */
/* Der Zugriff erfolgt direkt auf der Hardwareebene, d.h. ueber den Bild-    */
/* schirmspeicher bzw. die I/O-Ports der Grafikkarte.                        */
/*****************************************************************************/

#include "machine/io_port.h"

#define WHITE_ON_BLACK 0x0f
#define BLACK_ON_WHITE 0xf0


class CGA_Screen
{
private: 

   CGA_Screen(const CGA_Screen &copy); // Verhindere Kopieren

   void scroll_down();

   void calc_next_pos(int x, int y, int &x_to, int &y_to);
   
   int m_x, m_y;

public:

   CGA_Screen() : m_x(0), m_y(0);

   void show(int x, int y, char c, unsigned char attrib=BLACK_ON_WHITE);

   void setpos(int x, int y);

   void getpos(int &x, int &y);

   void print(char *text, int length, unsigned char attrib=BLACK_ON_WHITE);

   char get_char(int x, int y);

};

#endif
