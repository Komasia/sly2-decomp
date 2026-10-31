/* func_001E0650: appends a RELAYCK_WidgetHide command to the relay (oidWidget); asynchronous (the script does not wait for it). Called from the Splice binding func_001073B8. */
#include "relay.h"

void func_001E0650(RELAY *prelay, int oidWidget)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_WidgetHide, 1);
    prelaycmd->u.widgetHide.oidWidget = oidWidget;
}
