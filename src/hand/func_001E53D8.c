/* func_001E53D8: the script stops waiting on another relay: that relay's firing is ended (StopScptImpl__FP2LO) and the
 * wait is cleared. */
#include "relay.h"

void StopScptImpl__FP2LO(RELAY *prelay);

void func_001E53D8(JSG *pjsg)
{
    RELAY *prelayWait = pjsg->prelayWait;

    if (prelayWait != NULL) {
        StopScptImpl__FP2LO(prelayWait);
        pjsg->prelayWait = NULL;
    }
}
