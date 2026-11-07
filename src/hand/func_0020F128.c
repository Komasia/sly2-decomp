/* func_0020F128: increments the world counter cUnk3d80; the first reference starts ShowSubtitleBox__FP9DIALOGSUB on D_002E1E60. */
#include "sw.h"

extern char D_002E1E60[];
void ShowSubtitleBox__FP9DIALOGSUB(void *pv);

void func_0020F128(SW *psw)
{
    if (++psw->cUnk3d80 == 1) {
        ShowSubtitleBox__FP9DIALOGSUB(D_002E1E60);
    }
}
