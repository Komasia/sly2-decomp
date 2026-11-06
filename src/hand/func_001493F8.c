/* CloneVolbtn (Sly 1 button.c): clone the base object (func_002311B0, the XFM-level clone), then point the
 * cloned BTN component back at its new owner. */
#include "button.h"

void func_002311B0(VOLBTN *pvolbtn, VOLBTN *pvolbtnBase);

void CloneVolbtn__FP6VOLBTNT0(VOLBTN *pvolbtn, VOLBTN *pvolbtnBase)
{
    func_002311B0(pvolbtn, pvolbtnBase);
    pvolbtn->btn.paloOwner = pvolbtn;
}
