/* func_00175820: whether a contact may be acted on: not a contact flagged bit 48, nor from an object whose class flags
 * (+0xEC +0x70 bit 2) exclude it, nor a breakable when the job ignores them (+0x74); and not from a CID_STEP. */
#include "cid.h"
struct U { char pad[0x70]; unsigned long grf; };
struct LO { char pad[0xEC]; struct U *pcls; };
struct CONTACT { int pad; struct LO *plo; int pad2[2]; unsigned long grf; };
struct AIJOBX { char pad[0x74]; int fNoBreakables; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct LO *pcontact, int n);
int func_00175820(struct AIJOBX *pjob, struct CONTACT *pcontact) {
    if (pcontact->grf & (1UL << 48)) return 0;
    if (pcontact->plo->pcls->grf & 4) return 0;
    if (pjob->fNoBreakables && FIsBasicDerivedFrom__FP5BASIC3CID(pcontact->plo, CID_BREAKABLE)) return 0;
    return !FIsBasicDerivedFrom__FP5BASIC3CID(pcontact->plo, CID_STEP);
}
