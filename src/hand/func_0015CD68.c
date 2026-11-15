/* func_0015CD68: init the episode menu's screen object, reset its episodes / mode / sub-mode and make it
 * the one menu (D_003E1C04). */
#include "h2_epmenu.h"
extern EPMENU *D_003E1C04;
void InitLo__FP2LO(EPMENU *pepmenu);
void func_0015CD68(EPMENU *pepmenu)
{
    InitLo__FP2LO(pepmenu);
    pepmenu->cur = -1;
    pepmenu->next = -1;
    pepmenu->mode = -1;
    pepmenu->sub = -1;
    D_003E1C04 = pepmenu;
}
