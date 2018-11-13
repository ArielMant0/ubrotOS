/* $Id: cgascr.cc 5834 2013-10-08 17:04:08Z os $ */

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

#include "machine/cgascr.h"

#define CGA_START 0xb8000
#define MAX_X 80
#define MAX_Y 25 

void CGA_Screen::show(int x, int y, char c, unsigned char attrib)
{
  char *pos = (char*)(CGA_START + 2*(x + y*MAX_X));
  *pos = c;
  *(pos+1) = attrib;
}

void CGA_Screen::setpos(int x, int y)
{
  calc_next_pos(x, y, m_x, m_y);
  set_cursor();
}

void CGA_Screen::set_cursor()
{
    int pos = (int)(CGA_START + 2*(m_x + m_y*MAX_X));
    index.outb(14); // high
    data.outb(pos >> 8);
    index.outb(15); // low
    data.outb(pos);
}

void CGA_Screen::getpos(int &x, int &y)
{
  x = m_x;
  y = m_y;
}

void CGA_Screen::print(char *text, int length, unsigned char attrib)
{
  int x = m_x;
  int y = m_y;

  for (int i = 0; i < length; ++i)
  {
    if (text[i] != '\n')
    {
      show(x, y, text[i], attrib);
      calc_next_pos(x+1, y, x, y);
    }
    // new line
    else
    {
      calc_next_pos(0, y+1, x, y);
    }
  }
  setpos(x, y);
}

void CGA_Screen::calc_next_pos(int x, int y, int &x_to, int &y_to)
{
  if (x < 0 || y < 0)
  {
    print("Error in calc_next_pos\n", 23);
  }

  // Check if limit (x or y) is exceeded
  // -> new line (x)
  // -> scroll down (y)
  if (x >= MAX_X)
  {
    show(1, 0, 'F', 0xf0); // TODO
    calc_next_pos(0, y+1, x_to, y_to);
    return;
  }
  else if (y >= MAX_Y)
  {
    scroll_down();
    show(3, 0, 'F', 0xf0); // TODO
    y_to = y - 1;
    x_to = x;
  }
  else
  {
    x_to = x;
    y_to = y;
  }
}

void CGA_Screen::scroll_down()
{
  // for each row (bottom to top)
  for (int j = 1; j < MAX_Y; ++j)
  {
    // for each character in the line
    for (int i = 0; i < MAX_X; ++i)
    {
      char *pos = (char*)(CGA_START + 2*(i + j*MAX_X));
      show(i, j-1, *pos, *(pos+1));
    }
  }
  for (int i = 0; i < MAX_X; i++)
  {
    show(i, MAX_Y-1, ' ');
  }
}

char CGA_Screen::get_char(int x, int y)
{
  char *pos = (char*)(CGA_START + 2*(x+y*MAX_X));
  return *pos;
}

void CGA_Screen::print_error(char *filename, int length)
{
  setpos(0, 24);
  print("Error in: ", 10, 0x40);
  print(filename, length, 0x40);
}