/* func_001DFE80: fires the relay (func_001DFD58) with the player object (func_001C4840 of the world g_sw) as
 * the firer. Called from the Splice binding func_00106710. */
#include "relay.h"

extern char g_sw[];             /* the world (SW) */
LO *func_001C4840(void *psw);          /* the player object */
void func_001DFD58(RELAY *prelay, LO *ploFirer);   /* fire: run the relay's scripts */

void func_001DFE80(RELAY *prelay)
{
    func_001DFD58(prelay, func_001C4840(g_sw));
}
