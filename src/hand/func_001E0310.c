/* func_001E0310: appends a RELAYCK_WaitBlocks command to the relay: the script waits for the blocks labelled by the
 * oid-list argument (at most 4 are kept). Called from the Splice binding func_00106C08. */
#include "relay.h"
struct CRef { int tagk; int tag; };
void func_002013D8(struct CRef *pref, void *pvArgs, int cMin, int cMax, unsigned int *pc, OID *aoid);   /* read an oid list argument */
void CopyAb(void *pdst, void *psrc, int cb) asm("CopyAb__FPvT0Ui");
void Decref(struct CRef *pref) asm("Decref__4CRef");
void func_001E0310(RELAY *prelay, void *pvArgs)
{
    OID aoid[8];
    struct CRef ref;
    unsigned int coid;
    RELAYCMD *prelaycmd;
    func_002013D8(&ref, pvArgs, 6, 8, &coid, aoid);
    prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_WaitBlocks, 0);
    if (coid > 4) coid = 4;
    {
        unsigned int c = coid;
        prelaycmd->u.waitBlocks.coid = c;
        CopyAb(&prelaycmd->u.waitBlocks.aoid, aoid, c * 4);
    }
    Decref(&ref);
}
