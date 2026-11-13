/* SetAsegaEventSound: turn an animation segment player's sound flag on or off. While any ASEGA has it on, the game
 * keeps the pause reason 3 (PauseGame / ResumeGame on g_sw); a retracted ASEGA is left alone. */
#include "asega.h"

struct GAMEPAUSE;
extern struct GAMEPAUSE g_sw;
int FAsegaRetracted(ASEGA *pasega) asm("FAsegaRetracted__FP5ASEGA");
void PauseGame(struct GAMEPAUSE *pgp, int n) asm("PauseGame__FP9GAMEPAUSEi");
void ResumeGame(struct GAMEPAUSE *pgp, int n) asm("ResumeGame__FP9GAMEPAUSEi");

// name: SafeHouse port (SetAsegaEventSound)
void SetAsegaEventSound__FP5ASEGAi(ASEGA *pasega, int fSound)
{
    if (!FAsegaRetracted(pasega) && fSound != pasega->fSound) {
        if (fSound)
            PauseGame(&g_sw, 3);
        else
            ResumeGame(&g_sw, 3);
        pasega->fSound = fSound;
    }
}
