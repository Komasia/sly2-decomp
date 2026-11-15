/* func_001E1560: appends a RELAYCK_ButtonPrompt command to the relay (grfbtn, oidWho); the script waits for it to complete. */
#include "relay.h"

void func_001E1560(RELAY *prelay, int grfbtn, int oidWho)
{
    RELAYCMD *prelaycmd = PcmdNew__FP4SCPTii(prelay, RELAYCK_ButtonPrompt, 0);
    if (grfbtn == -1) grfbtn = 0x40;   /* default: the Cross button (joy.h PAD_CROSS) */
    prelaycmd->u.buttonPrompt.grfbtn = grfbtn;
    prelaycmd->u.buttonPrompt.oidWho = oidWho;
}
