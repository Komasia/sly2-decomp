/* class: a use (cid 0x23 family; SafeHouse jt.cpp: the loader's EOPID 1073 - each listed actor's +0x1000 bit ORed into the
 * use's players +0xFC). */
struct ACTOR {
    /* 0x0000 */ char pad0[0x1000];
    /* 0x1000 */ int grfPlayer;   /* the actor's player bit */
};
struct USE {
    /* 0x00 */ char pad0[0xfc];
    /* 0xfc */ int grfPlayers;   /* field: SafeHouse port - the players that may take it */
};

void func_00184028(struct USE *puse, struct ACTOR *pactor)
{
    puse->grfPlayers |= pactor->grfPlayer;
}
