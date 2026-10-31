/* func_001E0790: appends a RELAYCK_GotoLabelIf command to the relay (oidLabel, nValue); asynchronous (the script does not wait for it). Called from the Splice binding func_00107728. */
#include "relay.h"

void func_001E0790(RELAY *prelay, int oidLabel, int nValue)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_GotoLabelIf, 1);
    prelaycmd->u.gotoLabelIf.oidLabel = oidLabel;
    prelaycmd->u.gotoLabelIf.nValue = nValue;
}
