/* UpdateWatchA (0x20CE70): the guard's fall watcher: state 0 on the ground; 1 once there is nothing below it
 * (FWatchA); 2 when that lasted D_002C3DF0 and the guard is not busy with contact 0x4000 (vt slot 76); back to 0
 * when there is ground again. Field names: SafeHouse port (guard.h WATCHA). */
#include "vtbl.h"
struct GUARDV { char pad[0xC]; VTENT *pvt; };
struct WATCHA { struct GUARDV *pguard; int st; float t; int fOn; };
extern struct { float t; float dt; } g_clock;
extern float D_002C3DF0;   /* 0.1 */
int FWatchA__FP6WATCHA(struct WATCHA *pwatch);
void SetWatchA__FP6WATCHAi(struct WATCHA *pwatch, int st);

// name: SafeHouse port (UpdateWatchA)
void UpdateWatchA__FP6WATCHA(struct WATCHA *pwatch)
{
    int fFalling, st;
    if (!pwatch->fOn)
        return;
    fFalling = FWatchA__FP6WATCHA(pwatch);
    do {
        st = pwatch->st;
        switch (st) {
        case 0:
            if (fFalling)
                SetWatchA__FP6WATCHAi(pwatch, 1);
            break;
        case 1:
            if (!fFalling)
                SetWatchA__FP6WATCHAi(pwatch, 0);
            else if (g_clock.t - pwatch->t > D_002C3DF0 && !((int (*)(void *, int))pwatch->pguard->pvt[76].pfn)(VT_THIS(pwatch->pguard, &pwatch->pguard->pvt[76]), 0x4000))
                SetWatchA__FP6WATCHAi(pwatch, 2);
            break;
        case 2:
            if (!fFalling)
                SetWatchA__FP6WATCHAi(pwatch, 0);
            break;
        }
    } while (pwatch->st != st);
}
