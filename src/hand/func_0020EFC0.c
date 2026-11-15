/* PauseGame (0x20EFC0): pauses the game once more: the first pause takes the players' control (FUSR_HandsOff);
 * grf 1 also shows the subtitle box, grf 2 pauses the guards. */
#include "sw.h"
void AddGrfusr__Fi(int grfusr);
void func_0020F128(SW *psw);   /* the subtitle box */
void func_0020F198(SW *psw);   /* the guards */
#define GRFPAUSE_Subtitles 1
#define GRFPAUSE_Ai 2
// name: SafeHouse port (PauseGame)
void PauseGame__FP9GAMEPAUSEi(SW *psw, int grf)
{
    if (++psw->cHandsOff == 1) AddGrfusr__Fi(2);   /* FUSR_HandsOff */
    if (grf & GRFPAUSE_Subtitles) func_0020F128(psw);
    if (grf & GRFPAUSE_Ai) func_0020F198(psw);
}
