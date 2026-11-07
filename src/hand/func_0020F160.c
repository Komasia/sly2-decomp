/* func_0020F160: decrements the world counter cUnk3d80; the last reference runs HideSubtitleBox__FP9DIALOGSUB on D_002E1E60. */
#include "sw.h"

extern char D_002E1E60[];
void HideSubtitleBox__FP9DIALOGSUB(void *pv);

void func_0020F160(SW *psw)
{
    if (--psw->cUnk3d80 == 0) {
        HideSubtitleBox__FP9DIALOGSUB(D_002E1E60);
    }
}
