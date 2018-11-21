/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Behandlungs- */
/* routine fuer jeden Hardware-, Softwareinterrupt und jede Prozessor-       */
/* exception festlegen.                                                      */
/*****************************************************************************/

#include "machine/plugbox.h"

PlugBox::Plugbox ()
{

}

void PlugBox::assign (unsigned int slot, Gate& gate)
{

}

Gate& PlugBox::report (unsigned int slot)
{

}
