/* PcmdNew: appends a zeroed command of kind relayck to the relay and returns it; when the relay is full (its
 * crelaycmdMax, or 0x200 when that is unset) it returns the dummy command D_003DA740 instead. */
#include "relay.h"
extern RELAYCMD D_003DA740;        /* the dummy command (written to when full) */
void s1_memset(void *p, int b, int cb) asm("memset");
// name: SafeHouse port (PcmdNew)
RELAYCMD *PcmdNew__FP4SCPTii(RELAY *prelay, int relayck, int fAsync)
{
    RELAYCMD *prelaycmd;
    int crelaycmdMax = prelay->crelaycmdMax;
    if (crelaycmdMax <= -1) crelaycmdMax = 0x200;
    if (prelay->crelaycmd >= crelaycmdMax) return &D_003DA740;
    prelaycmd = &prelay->arelaycmd[prelay->crelaycmd++];
    s1_memset(prelaycmd, 0, sizeof(RELAYCMD));
    prelaycmd->relayck = relayck;
    prelaycmd->fAsync = fAsync;
    return prelaycmd;
}
