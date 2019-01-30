/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop ist ein Thread, der nichts weiter tut als einen Zaehler hochzu-      */
/* zaehlen und dies auf dem Bildschirm anzuzeigen. Zwischendurch gibt er     */
/* den Prozessor ab.                                                         */
/*****************************************************************************/

#ifndef __loop_include__
#define __loop_include__

#include "appl.h"
        
class Loop : public Application
{

private:

	int m_id, m_x, m_y, m_iter;

	void printGreeting(int count=0);

public:

	Loop (void* tos, int id, int x, int y, int iter=500) : 
		Application(tos),
		m_id(id),
		m_x(x),
		m_y(y),
		m_iter(iter) {} 

	void action() override;
};
 
#endif