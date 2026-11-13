/* class: JOBCOMPANIONATTACK, Bentley's attack job (SafeHouse actorai.h: JOBCOMPANION's case 2 ends on st == -1): done. */
struct JOBCOMPANIONATTACK {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int st;   /* field: SafeHouse port - -1 complete */
};

int func_00146298(struct JOBCOMPANIONATTACK *pjob)
{
    return pjob->st == -1;
}
