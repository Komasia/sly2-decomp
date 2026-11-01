/* func_001E53D8: the script stops waiting on another relay: that relay's firing is ended (func_001DFEB8) and the
 * wait is cleared. */
#include "relay.h"

void func_001DFEB8(RELAY *prelay);

void func_001E53D8(JSG *pjsg)
{
    RELAY *prelayWait = pjsg->prelayWait;

    if (prelayWait != NULL) {
        func_001DFEB8(prelayWait);
        pjsg->prelayWait = NULL;
    }
}
