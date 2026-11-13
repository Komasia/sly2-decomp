/* SetMoveHeading: turn the guard of a move reference toward a heading unless its heading is locked.
 * MOVEREF layout: SafeHouse port (guard.h). */
struct AIJOB;
struct GUARD;
struct MOVEREF {
    /* 0x0 */ struct AIJOB *pjob;       /* field: SafeHouse port */
    /* 0x4 */ int fHeadingLocked;       /* field: SafeHouse port */
    /* 0x8 */ int n8;
    /* 0xc */ struct GUARD *pguard;     /* field: SafeHouse port */
};
void SetStepPhysHeading(struct GUARD *pguard, float rad) asm("SetStepPhysHeading__FP3ALOf");

// name: SafeHouse port (SetMoveHeading)
void SetMoveHeading__FP7MOVEREF(struct MOVEREF *pmoveref, float rad)
{
    if (pmoveref->fHeadingLocked == 0)
        SetStepPhysHeading(pmoveref->pguard, rad);
}
