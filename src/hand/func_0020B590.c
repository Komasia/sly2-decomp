#include "vtbl.h"
struct GUARD {
    char pad0[0xC]; VTENT *pvt; char pad1[0x28 - 0x10]; unsigned long grfLo;
    char pad2[0xF64 - 0x30]; void *pdet; char pad3[0xFF8 - 0xF68]; float tFF8; int pad4; int nSpawnMode;
};
/* the guard manager: all of the world's guards */
struct GUARDMGR { char pad[0x50]; int cpguard; struct GUARD **apguard; };
struct AIMSG { int k; int an[27]; };
extern struct { float t; float dt; } g_clock;
extern float D_002C3DBC;   /* 0.25 */
extern const float D_002A88CC;
void UpdateLo__FP2LO(struct GUARDMGR *pmgr);
void *func_00205458(struct GUARD *pguard, int cid);   /* PjobFind */
void *s1_memset(void *pv, int c, int cb) asm("memset");
void React__8JOBREACTP5AIMSG(void *pjobreact, struct AIMSG *pmsg);
void func_00153FF8(void *pdet);   /* resets the detector entries */

/* UpdateGuardManager (0x20B590): each frame, every spawned guard in the world that was unregistered more than
 * D_002C3DBC ago is cleaned up by its spawn mode: 1 back to its pool (vt slot 9), 2 its patrol restarted (reaction
 * message 1) and its detector entries reset (0x153FF8). */
// name: SafeHouse port (UpdateGuardManager)
void UpdateGuardManager__FP2LO(struct GUARDMGR *pmgr)
{
    int i, cpguard;
    struct GUARD **apguard;
    UpdateLo__FP2LO(pmgr);
    cpguard = pmgr->cpguard;
    apguard = pmgr->apguard;
    for (i = 0; i < cpguard; i++) {
        struct GUARD *pguard = apguard[i];
        if (((int)(pguard->grfLo >> 60) & 1) && g_clock.t - pguard->tFF8 > D_002C3DBC) {
            switch (pguard->nSpawnMode) {
            case 0:
                break;
            case 1:
                ((void (*)(void *))pguard->pvt[9].pfn)(VT_THIS(pguard, &pguard->pvt[9]));
                break;
            case 2: {
                void *pjobreact = func_00205458(pguard, 0x9C);
                if (pjobreact) {
                    struct AIMSG msg;
                    s1_memset(&msg, 0, sizeof(msg));
                    msg.k = 1;
                    React__8JOBREACTP5AIMSG(pjobreact, &msg);
                }
                if (pguard->pdet)
                    func_00153FF8(pguard->pdet);
                break;
            }
            }
            pguard->tFF8 = D_002A88CC;
        }
    }
}
