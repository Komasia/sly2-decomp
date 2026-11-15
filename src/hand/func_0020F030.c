/* ResumeGame (0x20F030): one pause less: the last one gives the players their control back and drops a held Start
 * (pad button 8); grf 1 / 2 undo PauseGame's subtitle box / guards' pause. */
#include "sw.h"
struct JOYPS2;
extern struct JOYPS2 g_joy;
void RemoveGrfusr__Fi(int grfusr);
void ClearJoyBtns__FP6JOYPS2Ui(struct JOYPS2 *pjoy, int grfbtn);
void func_0020F160(SW *psw);   /* the subtitle box */
void func_0020F1A8(SW *psw);   /* the guards */
#define GRFPAUSE_Subtitles 1
#define GRFPAUSE_Ai 2
// name: SafeHouse port (ResumeGame)
void ResumeGame__FP9GAMEPAUSEi(SW *psw, int grf)
{
    if (--psw->cHandsOff == 0) {
        RemoveGrfusr__Fi(2);   /* FUSR_HandsOff */
        ClearJoyBtns__FP6JOYPS2Ui(&g_joy, 8);
    }
    if (grf & GRFPAUSE_Subtitles) func_0020F160(psw);
    if (grf & GRFPAUSE_Ai) func_0020F1A8(psw);
}
