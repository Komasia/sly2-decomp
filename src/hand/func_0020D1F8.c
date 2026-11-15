#include "so.h"
/* the watched water: its vtable and contact filter (+0x188) */
struct WATER { char pad[0xC]; VTENT *pvt; char pad2[0x188 - 0x10]; void *grfFilter; };
struct WATCHB { struct LO *pguard; int st; float t; struct WATER *pwater; int fOn; };
extern struct { float t; float dt; } g_clock;
extern float D_002C3E58;   /* 0: the delay before the contact */
qword PosOfLo__FP2LO(void *plo);
void SetWatchB__FP6WATCHBi(struct WATCHB *pwatch, int st);

/* UpdateWatchB (0x20D1F8): the guard's water watcher (the water set by the guard's messages 4 / 5): state 0 until the
 * guard's position is inside the water (its vt slot 73) while falling; then 1, and 2 (the water's contact) once the
 * guard is not busy with the water's filter (vt slot 76); back to 0 when the water is gone or the guard is busy
 * again. Field names: SafeHouse port (guard.cpp UpdateWatchB). */
// name: SafeHouse port (UpdateWatchB)
void UpdateWatchB__FP6WATCHB(struct WATCHB *pwatch)
{
    int st;
    if (!pwatch->fOn)
        return;
    do {
        st = pwatch->st;
        switch (st) {
        case 0: {
            struct WATER *pwater = pwatch->pwater;
            int fIn;
            VTENT *pe;
            void *pthis;
            if (!pwater)
                break;
            fIn = 0;
            pe = &pwater->pvt[73];
            pthis = VT_THIS(pwater, pe);
            if (((int (*)(void *, qword))pe->pfn)(pthis, PosOfLo__FP2LO(pwatch->pguard))) {
                qword vel = ((qword (*)(void *))pwatch->pguard->pvt[33].pfn)(VT_THIS(pwatch->pguard, &pwatch->pguard->pvt[33]));
                float z;
                __asm__("pextuw %0, $zero, %1" : "=r"(z) : "r"(vel));
                if (z < 0.0f)
                    fIn = 1;
            }
            if (fIn)
                SetWatchB__FP6WATCHBi(pwatch, 1);
            break;
        }
        case 1:
            if (!pwatch->pwater)
                SetWatchB__FP6WATCHBi(pwatch, 0);
            else if (g_clock.t - pwatch->t > D_002C3E58 &&
                     !((int (*)(void *, void *))pwatch->pguard->pvt[76].pfn)(VT_THIS(pwatch->pguard, &pwatch->pguard->pvt[76]), pwatch->pwater->grfFilter))
                SetWatchB__FP6WATCHBi(pwatch, 2);
            break;
        case 2:
            if (!pwatch->pwater || ((int (*)(void *, void *))pwatch->pguard->pvt[76].pfn)(VT_THIS(pwatch->pguard, &pwatch->pguard->pvt[76]), pwatch->pwater->grfFilter))
                SetWatchB__FP6WATCHBi(pwatch, 0);
            break;
        }
    } while (pwatch->st != st);
}
