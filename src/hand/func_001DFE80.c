/* func_001DFE80: fires the relay (StartScptImpl__FP2LOi) with the player object (PloPlayerPo__FP2SW of the world g_sw) as
 * the firer. Called from the Splice binding func_00106710. */
#include "relay.h"

extern char g_sw[];             /* the world (SW) */
LO *PloPlayerPo__FP2SW(void *psw);          /* the player object */
void StartScptImpl__FP2LOi(RELAY *prelay, LO *ploFirer);   /* fire: run the relay's scripts */

void func_001DFE80(RELAY *prelay)
{
    StartScptImpl__FP2LOi(prelay, PloPlayerPo__FP2SW(g_sw));
}
