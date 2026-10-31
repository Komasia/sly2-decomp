/* func_001E0610: appends a RELAYCK_WidgetShow command to the relay (oidWidget, idLabel); fAsync from the caller. Called from the Splice binding func_00107300. */
#include "relay.h"

void func_001E0610(RELAY *prelay, int oidWidget, int idLabel, int fAsync)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_WidgetShow, fAsync);
    prelaycmd->u.widgetShow.oidWidget = oidWidget;
    prelaycmd->u.widgetShow.idLabel = idLabel;
}
