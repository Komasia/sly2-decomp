/* func_001DE400: Init of the laser (class 0x55, CID_LASER): the class 0x54 init (func_001DE2A0), the moving-endpoint
 * speed multiplier 1.0, clears bit 35 of the SO flags qword (so.h SO::fUnk35), then sets update flag GRFUPD_Unk8. */
#include "h3_update.h"
#define GRFSO_Unk35 0x800000000UL   /* bit 35 of SO +0x148 */

typedef struct LASER {
    /* 0x000 */ char unk_lo0[0x40];
    /* 0x040 */ int grfUpd;           /* LO +0x40 update flags, or a pointer to them (h3_update.h) */
    /* 0x044 */ char unk_lo44[0x148 - 0x44];
    /* 0x148 */ unsigned long grfSo;  /* SO +0x148 flags qword */
    /* 0x150 */ char unk_150[0x1C0 - 0x150];
    /* 0x1c0 */ float rSpeed;         /* moving-endpoint speed multiplier (field: SafeHouse port, laser.cpp +0x1C0) */
} LASER;
void func_001DE2A0(LASER *plaser);

void func_001DE400(LASER *plaser)
{
    int grf;
    func_001DE2A0(plaser);
    plaser->rSpeed = 1.0f;
    plaser->grfSo &= ~GRFSO_Unk35;
    grf = plaser->grfUpd;
    if ((grf ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grf |= GRFUPD_Unk8;
    else plaser->grfUpd = grf | GRFUPD_Unk8;
}
