/* JOBSHOOT::Message: while shooting, the gun clip's animation events (message 9 from the move child's entry) 0x31 /
 * 0x32 set / clear the guard's shooting flag (+0xF60); else the base handling. */
#include "h2_aijobs.h"

/* message 9 (ASEGMSG9): n0 the ASEGA, nEvent the event */
struct ASEGMSG9 { int n0; int n4; int nEvent; };
struct KINDE;
struct GUARD {
    /* 0x000 */ char pad0[0xF60];
    /* 0xf60 */ int fShooting;          /* field: SafeHouse port (fF60) */
};
int PasegaOfKinde__FP5KINDE(struct KINDE *pkinde);
int Message__5AIJOBiPv(JOBSHOOT *pjob, int msg, struct ASEGMSG9 *pmsg);

// name: SafeHouse port (JOBSHOOT::Message)
int Message__8JOBSHOOTiPv(JOBSHOOT *pjob, int msg, struct ASEGMSG9 *pmsg)
{
    if (msg == 9 && !pjob->st && ((JOBMOVE *)pjob->aijob.pchild)->pkinde && PasegaOfKinde__FP5KINDE(((JOBMOVE *)pjob->aijob.pchild)->pkinde) == pmsg->n0) {
        switch (pmsg->nEvent) {
        case 0x31: pjob->aijob.pguard->fShooting = 1; return 1;
        case 0x32: pjob->aijob.pguard->fShooting = 0; return 1;
        }
    }
    return Message__5AIJOBiPv(pjob, msg, pmsg);
}
