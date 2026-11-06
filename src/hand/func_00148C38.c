/* PostButtonLoad (Sly 1 button.c): the SO post-load, then the BTN component's post-load, then the button's
 * initial state (func_001490A0(pbutton, 0)). */
#include "button.h"

void func_001F36A8(SO *pso);            /* SO post-load (base of the PostLoad slot) */
void func_00148740(BTN *pbtn);          /* BTN post-load */
void func_001490A0(BUTTON *pbutton, int n);

void PostButtonLoad__FP6BUTTON(BUTTON *pbutton)
{
    func_001F36A8(&pbutton->so);
    func_00148740(&pbutton->btn);
    func_001490A0(pbutton, 0);
}
