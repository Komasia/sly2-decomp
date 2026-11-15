/* func_0020F128 (0x20F128): PauseGame's grf 1: the first one shows the subtitle box (D_002E1E60). */
#include "sw.h"

extern char D_002E1E60[];
void ShowSubtitleBox__FP9DIALOGSUB(void *pv);

void func_0020F128(SW *psw)
{
    if (++psw->cSubtitles == 1) {
        ShowSubtitleBox__FP9DIALOGSUB(D_002E1E60);
    }
}
