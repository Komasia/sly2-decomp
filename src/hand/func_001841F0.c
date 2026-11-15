/* class: a use (cid 0x23 family; SafeHouse jt.h, orig 0x1841F0: may that player take the use - its players +0xFC AND the
 * actor's +0x1000). */
#include "actor.h"
struct USE {
    /* 0x00 */ char pad0[0xfc];
    /* 0xfc */ int grfPlayers;   /* field: SafeHouse port */
};

int func_001841F0(struct USE *puse, struct ACTOR *pactor)
{
    return (puse->grfPlayers & pactor->grfPlayer) != 0;
}
