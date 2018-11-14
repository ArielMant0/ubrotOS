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

   void read_cursor();
   
   int m_x, m_y;
   IO_Port index, data;

public:

    // high bits: background, low bits: foreground
    enum Color : unsigned char {
        black = 0x00,
        blue,
        green,
        cyan,
        red,
        magenta,
        brown,
        light_gray,
        dark_grey,
        light_blue,
        light_green,
        light_cyan,
        light_red,
        light_magenta,
        yellow,
        white
    };

    CGA_Screen();

   void show(int x, int y, char c, unsigned char attrib=char(Color::white));

   void setpos(int x, int y);

   void getpos(int &x, int &y);

   void print(char *text, int length, unsigned char attrib=char(Color::white));

   char get_char(int x, int y);

   void print_error(char *filename, int length);

};

#endif
