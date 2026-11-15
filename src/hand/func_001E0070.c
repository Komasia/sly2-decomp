/* func_001E0070: removes an alarm (oid) from the relay's alarm list (SafeHouse scpt.cpp: RemoveAlarm). */
#include "relay.h"
void *s1_memmove(void *d, void *s, int cb) asm("memmove");
void func_001E0070(RELAY *prelay, OID oidAlarm)
{
    int i;
    for (i = 0; i < prelay->calarm; i++) {
        if (prelay->aoidAlarm[i] == oidAlarm) {
            s1_memmove(prelay->aoidAlarm + i, prelay->aoidAlarm + i + 1, (prelay->calarm - i) * 4 - 4);
            prelay->calarm--;
            return;
        }
    }
}
