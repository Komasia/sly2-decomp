/* func_001E7A28: rope option 1046's setter (EOPID 1212): the rope's mode; ROPEK_None turns the path's rope update
 * off (GRFUPD_Unk20 on, GRFUPD_Rope off), any other mode makes the rope and turns it on (SafeHouse rope.cpp).
 * The update flags word (LO +0x40): h3_update.h. */
#include "h3_rope.h"
#include "h3_update.h"

/* the path object as this file sees it */
struct PATHUPD {
    /* 0x000 */ char pad0[0x40];
    /* 0x040 */ int grfUpd;             /* LO +0x40: the update flags or a pointer to them */
    /* 0x044 */ char pad44[0x17c - 0x44];
    /* 0x17c */ ROPE *prope;            /* crv.h CRV::prope */
};
ROPE *PropeEnsure__FP2LOi(struct PATHUPD *ppath, int f);
void func_001A6CA8(struct PATHUPD *ppath, int n);
void func_001E7A28(struct PATHUPD *ppath, int mode)
{
    if (mode != ROPEK_None) {
        PropeEnsure__FP2LOi(ppath, 1);
        func_001A6CA8(ppath, 0);
        { int grf = ppath->grfUpd; if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grf &= ~GRFUPD_Unk20; else ppath->grfUpd = grf & ~GRFUPD_Unk20; }
        { int grf = ppath->grfUpd; if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grf |= GRFUPD_Rope; else ppath->grfUpd = grf | GRFUPD_Rope; }
    } else {
        func_001A6CA8(ppath, 0);
        { int grf = ppath->grfUpd; if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grf |= GRFUPD_Unk20; else ppath->grfUpd = grf | GRFUPD_Unk20; }
        { int grf = ppath->grfUpd; if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grf &= ~GRFUPD_Rope; else ppath->grfUpd = grf & ~GRFUPD_Rope; }
    }
    if (ppath->prope) ppath->prope->mode = mode;
}
