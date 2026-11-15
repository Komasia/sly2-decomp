/* JOBGOTO::Init (0xBA): no state, no guard state, the search never done, and the navigation's serial (the world's
 * +0x45CC object's +0x28) remembered. Layout: SafeHouse port (aijobs.h JOBGOTO). */
#include "aijob.h"

struct NAVSERIAL { char pad0[0x28]; int nSerial; };
struct SW { char pad0[0x45CC]; struct NAVSERIAL *pnavserial; };
extern struct SW g_sw;
struct JOBGOTO {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                  /* field: SafeHouse port */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ int nAnim;               /* field: SafeHouse port - the guard state (-1 none) */
    /* 0x3c */ char pad3C[0xA0 - 0x3C];
    /* 0xa0 */ float tSearch;           /* field: SafeHouse port */
    /* 0xa4 */ int nSerial;             /* field: SafeHouse port */
};
void Init__5AIJOB(struct JOBGOTO *pjob);

// name: SafeHouse port (JOBGOTO::Init)
void Init__7JOBGOTO(struct JOBGOTO *pjob)
{
    Init__5AIJOB(pjob);
    pjob->st = -1;
    pjob->nAnim = -1;
    pjob->tSearch = -3.40282346638528859812e+38f;
    pjob->nSerial = g_sw.pnavserial->nSerial;
}
