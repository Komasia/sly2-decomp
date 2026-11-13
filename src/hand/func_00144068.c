/* class: ACTOR (SafeHouse actor.h / pad.cpp EOPID 759: the actor is busy - its AI jobs +0x270 or a script driving it). */
struct ACTOR {
    /* 0x0000 */ char pad0[0x270];
    /* 0x0270 */ int cJob;   /* field: SafeHouse port (n270) - busy when positive */
    /* 0x0274 */ char pad274[0x1084 - 0x274];
    /* 0x1084 */ void *prunScript;   /* field: SafeHouse port - the script runner driving it */
};

int func_00144068(struct ACTOR *pactor)
{
    int fBusy = 0;
    if (pactor->cJob > 0 || pactor->prunScript != 0) {
        fBusy = 1;
    }
    return fBusy;
}
