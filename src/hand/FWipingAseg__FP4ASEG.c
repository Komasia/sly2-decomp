/* FWipingAseg (0x1E00E8): whether the relay has the alarm (oid) in its alarm list (SafeHouse scpt.cpp: FHasAlarm).
 * The function's name is kept for its symbol; the object is a relay (relay.h), not an ASEG. */
#include "relay.h"
int FWipingAseg__FP4ASEG(RELAY *prelay, OID oidAlarm)
{
    int i;
    for (i = 0; i < prelay->calarm; i++) {
        if (prelay->aoidAlarm[i] == oidAlarm) return 1;
    }
    return 0;
}
