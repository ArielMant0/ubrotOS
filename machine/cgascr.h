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

class CGA_Screen
{
private: 

   CGA_Screen(const CGA_Screen &copy); // Verhindere Kopieren

   void scroll_down();

   void calc_next_pos(int x, int y, int &x_to, int &y_to, bool scroll=true);

   void set_cursor();
   
   int m_x, m_y;
   IO_Port index, data;

public:

    /**
     * Enum that specifies all color attributes for the screen
     *  1. color = background
     *  2. color = foreground
     */
    enum Attributes : unsigned char { // TODO
        white_black = 0x0f,
        black_white = 0xf0
    };

    CGA_Screen() : m_x(0), m_y(0), index(0x3d4), data(0x3d5) {}

   void show(int x, int y, char c, unsigned char attrib=char(black_white));

   void setpos(int x, int y);

   void getpos(int &x, int &y);

   void print(char *text, int length, unsigned char attrib=char(black_white));

   char get_char(int x, int y);

   void print_error(char *filename, int length);

};

#endif
