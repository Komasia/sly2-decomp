/* The head's look ranges: pan, tilt and the roll at the pan range's ends (+0x1120..). SafeHouse port (actor.h). */
struct S8 { float a, b; };
struct ACTOR { char pad[0x1120]; struct S8 lmPan, lmTilt, lmRoll; };   /* field: SafeHouse port (pan / tilt ranges, the roll at the pan ends) */
void func_00143090(struct ACTOR *pactor, struct S8 *plmPan, struct S8 *plmTilt, struct S8 *plmRoll)
{
    pactor->lmPan = *plmPan;
    pactor->lmTilt = *plmTilt;
    pactor->lmRoll = *plmRoll;
}
