/* LoadButtonFromBrx (Sly 1 button.c): load the SO part, then set up the BTN component (Sly 1: LoadBtn). */
#include "button.h"

class CBinaryInputStream;

void LoadSoFromBrx(SO *pso, CBinaryInputStream *pbis);
extern "C" void func_00148738(BTN *pbtn, BUTTON *pbutton);   /* Sly 1 LoadBtn(BTN *, ALO *paloOwner) */

void LoadButtonFromBrx(BUTTON *pbutton, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(&pbutton->so, pbis);
    func_00148738(&pbutton->btn, pbutton);
}
