/* PropeEnsure: a path's rope simulation, made on first use (0x90 bytes, InitRope): then the path's distances
 * (RecalcCrv) and its update in the physics loop (func_001A6CA8, update flags: GRFUPD_Unk20 off, GRFUPD_Rope on);
 * f 1 on an existing one: the update re-armed (GRFUPD_Unk4). The update flags word (LO +0x40) holds the flags
 * (GRFUPD_Flags set) or points at them (h3_update.h). Layout: the path's LO part, crv.h CRV +0x17C. */
#include "h3_rope.h"
#include "h3_update.h"

/* the path object as this file sees it */
struct PATHUPD {
    /* 0x000 */ char pad0[0x40];
    /* 0x040 */ int grfUpd;             /* LO +0x40: the update flags or a pointer to them */
    /* 0x044 */ char pad44[0x17c - 0x44];
    /* 0x17c */ ROPE *prope;            /* crv.h CRV::prope */
};
void *__builtin_new(int cb);
ROPE *InitRope__FP4ROPEP2LO(void *pv, struct PATHUPD *ppath);
void RecalcCrv__FP3CRV(struct PATHUPD *ppath);
void func_001A6CA8(struct PATHUPD *ppath, int n);
// name: SafeHouse port (PropeEnsure)
ROPE *PropeEnsure__FP2LOi(struct PATHUPD *ppath, int f)
{
    if (!ppath->prope) {
        ppath->prope = InitRope__FP4ROPEP2LO(__builtin_new(0x90), ppath);
        RecalcCrv__FP3CRV(ppath);
        func_001A6CA8(ppath, 0);
        { int grf = ppath->grfUpd; if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grf &= ~GRFUPD_Unk20; else ppath->grfUpd = grf & ~GRFUPD_Unk20; }
        { int grf = ppath->grfUpd; if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grf |= GRFUPD_Rope; else ppath->grfUpd = grf | GRFUPD_Rope; }
    } else if (f == 1) {
        func_001A6CA8(ppath, 0);
        { int grf = ppath->grfUpd; if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grf |= GRFUPD_Unk4; else ppath->grfUpd = grf | GRFUPD_Unk4; }
    }
    return ppath->prope;
}
