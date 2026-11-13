/* SetDanceState: the tango's state: leaving 1 resumes the game (3), entering 1 pauses it; the beats are cleared.
 * Layout: SafeHouse port (dance.cpp DANCE). */
#include "clock.h"

struct DANCE {
    /* 0x000 */ char pad0[0x50];
    /* 0x050 */ int state;     /* field: SafeHouse port */
    /* 0x054 */ float t54;     /* field: SafeHouse port */
    /* 0x058 */ char pad58[0x1c0 - 0x58];
    /* 0x1c0 */ int cbeat;     /* SafeHouse: abeat */
};
extern char g_sw[];
void ResumeGame__FP9GAMEPAUSEi(void *psw, int n);
void PauseGame__FP9GAMEPAUSEi(void *psw, int n);

// name: SafeHouse port (SetDanceState)
void SetDanceState__FP5DANCEi(struct DANCE *pdance, int state)
{
    int stateOld = pdance->state;
    if (stateOld != state) {
        if (stateOld == 1)
            ResumeGame__FP9GAMEPAUSEi(g_sw, 3);
        pdance->state = state;
        pdance->t54 = g_clock.t;
        pdance->cbeat = 0;
        if (state == 1)
            PauseGame__FP9GAMEPAUSEi(g_sw, 3);
    }
}
