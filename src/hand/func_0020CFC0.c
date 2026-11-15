/* func_0020CFC0 (0x20CFC0): FWatchA's line-test filter: a sensor entry (flag bit 48) of a cid 0x59 object counts,
 * the rest as 0x20FA50 decides. */
#include "cid.h"
struct SOE { int unk_0x00; void *palo; char pad[8]; long grf; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int func_0020FA50(void *pv, struct SOE *psoe);
int func_0020CFC0(void *pv, struct SOE *psoe) { if ((psoe->grf & 0x1000000000000L) && FIsBasicDerivedFrom__FP5BASIC3CID(psoe->palo, CID_WATER)) return 1; return func_0020FA50(pv, psoe); }
