/* SetActorZone: the current player's camera zone (+0x1024): the old one's forcing off, the new one's on
 * (SetZoneForced). Other actors are ignored. Source: SafeHouse port (interact.cpp). */
#include "actor.h"
struct LO;
extern char g_sw[];
struct ACTOR *PloPlayerPo__FP2SW(void *psw);
void SetZoneForced__FP2LOi(struct LO *plo, int fForced);

// name: SafeHouse port (SetActorZone)
void SetActorZone__FP5ACTORP2LO(struct ACTOR *pactor, struct LO *plo)
{
    struct ACTOR *pactorPlayer = PloPlayerPo__FP2SW(g_sw);
    if (pactorPlayer == pactor) {
        if (pactorPlayer->ploZone != 0)
            SetZoneForced__FP2LOi(pactorPlayer->ploZone, 0);
        pactorPlayer->ploZone = plo;
        if (plo != 0)
            SetZoneForced__FP2LOi(plo, 1);
    }
}
