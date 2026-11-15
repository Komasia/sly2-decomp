/* JOBUSE::Update: the move goes on; a use with an orientation turns the guard's move frame to it while the move is in
 * its state 0 and the entry's player's +0x10 is 2 or more. */
#include "h2_aijobs.h"

struct MOVEREF { struct AIJOB *pjob; int fHeadingLocked; int n8; struct GUARD *pguard; };  /* field: SafeHouse port */
struct GUARD {
    /* 0x000 */ char pad0[0xFD0];
    /* 0xfd0 */ struct MOVEREF move;    /* field: SafeHouse port */
};
struct PLAYER { char pad0[0x10]; int n10; };
struct KINDE { int k; void *pv; struct PLAYER *pvState; int grf; };   /* field: SafeHouse port (guard.h KINDE) */
void Update__7JOBMOVE(JOBUSE *pjob);
void func_00209840(struct MOVEREF *pmove, qword *pmat);   /* the move's frame set */

// name: SafeHouse port (JOBUSE::Update)
void Update__6JOBUSE(JOBUSE *pjob)
{
    Update__7JOBMOVE(pjob);
    if (pjob->fBasis && !pjob->jobmove.st && pjob->jobmove.pkinde->pvState->n10 >= 2)
        func_00209840(&pjob->jobmove.aijob.pguard->move, pjob->mat);
}
