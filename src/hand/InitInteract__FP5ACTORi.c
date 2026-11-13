/* InitInteract: the players' interaction sub-object (an actor's +0x4C0): its owner, no states (-1), its two gaits
 * (0x6F) and its reach (+0x440). Layout: SafeHouse port (interact.h INTERACT). */
struct ALO;
struct GAIT { char ab[0xc0]; };
struct REACH { char ab[0xb0]; };
struct INTERACT {
    /* 0x000 */ struct ALO *palo;
    /* 0x004 */ int n4;
    /* 0x008 */ int n4C8;          /* field: SafeHouse port (the actor's +0x4C8) */
    /* 0x00c */ int nSub4CC;       /* field: SafeHouse port (the actor's +0x4CC) */
    /* 0x010 */ char pad10[0x180 - 0x10];
    /* 0x180 */ struct GAIT gait180;   /* field: SafeHouse port */
    /* 0x240 */ struct GAIT gait240;   /* field: SafeHouse port */
    /* 0x300 */ char pad300[0x440 - 0x300];
    /* 0x440 */ struct REACH reach;
    /* 0x4f0 */ char pad4f0[0x4fc - 0x4f0];
    /* 0x4fc */ int n9BC;          /* field: SafeHouse port (the actor's +0x9BC) */
};
void InitGait(struct GAIT *pgait, struct ALO *palo, int n) asm("InitGait__FP4GAITii");
void func_001CC158(struct REACH *preach);   /* the reach's init */

// name: SafeHouse port (InitInteract)
void InitInteract__FP5ACTORi(struct INTERACT *pinter, struct ALO *palo)
{
    pinter->palo = palo;
    pinter->n4C8 = -1;
    pinter->nSub4CC = -1;
    pinter->n9BC = -1;
    InitGait(&pinter->gait180, palo, 0x6F);
    InitGait(&pinter->gait240, palo, 0x6F);
    func_001CC158(&pinter->reach);
}
