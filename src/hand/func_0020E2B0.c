/* func_0020E2B0 (0x20E2B0): of the world's (at most 16) CID_ALO_31 (0x31) objects the one with the highest +0xB8 gives the
 * world's +0x3E5C (its +0xC8) and is set with 0xFF (0x1A6D28). */
#include "cid.h"
struct LO31 { char pad[0xB8]; int nPriority; char p2[0xC]; int nC8; };
struct SW { char pad[0x3E5C]; int n3E5C; };
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct SW *psw, int grffso, int cid, int a, int cploMax, struct LO31 **aplo);
void func_001A6D28(struct LO31 *plo, int n);
void func_0020E2B0(struct SW *psw)
{
    struct LO31 *aplo[16];
    int cplo = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(psw, 5, CID_ALO_31, 0, 16, aplo);
    int nMax = 0;
    struct LO31 *ploBest = 0;
    int i;
    for (i = 0; i < cplo; i++) {
        if (aplo[i]->nPriority > nMax) {
            nMax = aplo[i]->nPriority;
            ploBest = aplo[i];
        }
    }
    if (ploBest) {
        psw->n3E5C = ploBest->nC8;
        func_001A6D28(ploBest, 0xFF);
    }
}
