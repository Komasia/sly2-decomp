/* StartAnimatedOverlay: an overlay started with an animation and a dialog: closing, skipping and input allowed, the
 * animation (the ASEG nearest the overlay with that oid) made to run on the real clock (its update flags +0x40 get
 * GRFUPD_RealTime) and applied to the overlay from its start, then state 0. Layout: SafeHouse port (overlay.cpp). */
extern char g_sw[];
struct ASEG {
    /* 0x00 */ char pad[0x40];
    /* 0x40 */ unsigned int grfUpd;   /* the update flags (low bit set) or a pointer to them */
};
struct OVERLAY {
    /* 0x000 */ char pad[0x160];
    /* 0x160 */ char pasega[4];   /* field: SafeHouse port - the animation (its address is passed) */
    /* 0x164 */ int canClose;     /* field: SafeHouse port */
    /* 0x168 */ int canSkip;      /* field: SafeHouse port */
    /* 0x16c */ int accepts;      /* field: SafeHouse port */
    /* 0x170 */ int dialog;       /* field: SafeHouse port */
};
#define GRFUPD_Flags    0x001   /* SafeHouse update.h: the word holds the flags, not a pointer */
#define GRFUPD_RealTime 0x100   /* updated on the real clock too */
void *PloFindSwNearest__FP2LO3OIDii(void *psw, int grffso, int oid, void *ploNear);
void ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA(void *paseg, void *palo, float tLocal, float svt, int n, void *ppasega);
void func_00147410(struct OVERLAY *poverlay, int state);   /* the overlay's state */
// name: SafeHouse port (StartAnimatedOverlay)
void StartAnimatedOverlay__FP2LOii(struct OVERLAY *poverlay, int oidAseg, int dialog)
{
    struct ASEG *paseg;
    poverlay->dialog = dialog;
    poverlay->accepts = 1;
    poverlay->canSkip = 1;
    poverlay->canClose = 1;
    paseg = PloFindSwNearest__FP2LO3OIDii(g_sw, 1, oidAseg, poverlay);
    if (paseg) {
        unsigned int grfUpd = paseg->grfUpd;
        if ((grfUpd ^ GRFUPD_Flags) & GRFUPD_Flags) *(int *)grfUpd |= GRFUPD_RealTime;
        else paseg->grfUpd = grfUpd | GRFUPD_RealTime;
        ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA(paseg, poverlay, 0.0f, 1.0f, 4, poverlay->pasega);
        func_00147410(poverlay, 0);
    }
}
