/* ClearJoyBtns__FP6JOYPS2Ui: forgets the given buttons: they count as neither down nor latched. */
#include "joy.h"

// name: SafeHouse port (ClearJoyBtns)
extern "C" void ClearJoyBtns__FP6JOYPS2Ui(JOY *pjoy, uint grfbtn)
{
    uint grfbtnKeep = ~grfbtn;
    pjoy->grfbtn &= grfbtnKeep;
    pjoy->grfbtnLatched &= grfbtnKeep;
}
