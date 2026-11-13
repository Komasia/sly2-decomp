/* JOBSCRIPT::SeekMarker (EOPID 1359): the command cursor moved to a marker of the list (0x1711F0: the first kind-9
 * marker command of that oid) without executing it; a running command's child job is ended first.
 * Layout: SafeHouse port (aijobs.h JOBSCRIPT). */
#include "aijob.h"

struct CMDLIST;
struct CMD;
struct JOBSCRIPT {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct CMDLIST *pcmdlist;   /* field: SafeHouse port */
    /* 0x34 */ void *ploNear;              /* field: SafeHouse port */
    /* 0x38 */ struct CMD *pcmd;           /* field: SafeHouse port - the current command */
    /* 0x3c */ float tCmd;                 /* field: SafeHouse port */
    /* 0x40 */ int fRunning;               /* field: SafeHouse port */
};
void EndChildJob__FPP5AIJOB(AIJOB **ppjob);
struct CMD *func_001711F0(struct CMDLIST *pcmdlist, int oid);   /* SafeHouse: the marker command of an oid */

// name: SafeHouse port (JOBSCRIPT::SeekMarker)
void SeekMarker__9JOBSCRIPT3OID(struct JOBSCRIPT *pjob, int oid)
{
    if (pjob->pcmdlist != 0) {
        if (pjob->fRunning) {
            EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
            pjob->fRunning = 0;
        }
        pjob->pcmd = func_001711F0(pjob->pcmdlist, oid);
    }
}
