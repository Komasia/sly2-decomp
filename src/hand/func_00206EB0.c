#include "cid.h"
/* the script job (cid 0xA9) */
struct JOBSCRIPT { char pad[0x4C]; int fFromReact; };
int FGuardState(void *pguard, int st) asm("FGuardState__FP5GUARDi");
struct JOBSCRIPT *func_00205458(void *pguard, int cid);   /* PjobFind */
int func_00206D48(void *pguard);   /* one of the special guard families */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);

/* FGuardModeAllowed (0x206EB0): whether the guard may enter mode nMode: -1 always; nothing while in state 7 or while a
 * script job started by a reaction runs; modes 8 / 13 / 14 always; mode 21 not for classes 0x3E / 0x42 / 0x43;
 * modes 34 / 37 not for the special guard families; mode 11 only for the plain guards. */
// name: SafeHouse port (FGuardModeAllowed)
int FGuardModeAllowed__FP5GUARDi(void *pguard, int nMode)
{
    struct JOBSCRIPT *pjob;
    if (nMode == -1)
        return 1;
    if (FGuardState(pguard, 7))
        return 0;
    pjob = func_00205458(pguard, 0xA9);
    if (pjob && pjob->fFromReact)
        return 0;
    switch (nMode) {
    case 8:
    case 0xD:
    case 0xE:
        return 1;
    case 0x15:
        return !(FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x3E) || FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x42) || FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x43));
    case 0x22:
    case 0x25:
        return !func_00206D48(pguard);
    case 0xB:
        return !(FIsBasicDerivedFrom__FP5BASIC3CID(pguard, CID_DIMITRI) || FIsBasicDerivedFrom__FP5BASIC3CID(pguard, CID_RAJAN) || FIsBasicDerivedFrom__FP5BASIC3CID(pguard, CID_CONTESSA) ||
                 FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x3E) || FIsBasicDerivedFrom__FP5BASIC3CID(pguard, CID_ARPEGGIO) || FIsBasicDerivedFrom__FP5BASIC3CID(pguard, CID_CARMELITA) ||
                 FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x3C) || FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x42) || FIsBasicDerivedFrom__FP5BASIC3CID(pguard, 0x43));
    }
    return 0;
}
