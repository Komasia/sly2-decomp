/* func_0020F160 (0x20F160): ResumeGame's grf 1: the last one hides the subtitle box (D_002E1E60). */
#include "sw.h"

extern char D_002E1E60[];
void HideSubtitleBox__FP9DIALOGSUB(void *pv);

void func_0020F160(SW *psw)
{
    if (--psw->cSubtitles == 0) {
        HideSubtitleBox__FP9DIALOGSUB(D_002E1E60);
    }
}
