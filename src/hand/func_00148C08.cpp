/* LoadButtonFromBrx (Sly 1 button.c): load the SO part, then set up the BTN component (Sly 1: LoadBtn). */
#include "button.h"

class CBinaryInputStream;

void LoadSoFromBrx(SO *pso, CBinaryInputStream *pbis);
extern "C" void LoadBtn(BTN *pbtn, BUTTON *pbutton) asm("LoadBtn__FP3BTNP3ALO");   /* Sly 1 LoadBtn(BTN *, ALO *paloOwner) */

void LoadButtonFromBrx(BUTTON *pbutton, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(&pbutton->so, pbis);
    LoadBtn(&pbutton->btn, pbutton);
}
