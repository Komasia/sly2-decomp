/* StartPrizeInteract: an actor holds up a prize (interaction kind 12) with the given clip, else the interaction's
 * default one. Layout: SafeHouse port (interact.h INTERACT at ACTOR +0x4C0). */
struct ASEG;
struct LO;
struct INTERACT {
    /* 0x000 */ char pad0[0x508];
    /* 0x508 */ struct ASEG *paseg508;   /* field: SafeHouse port - kind 12's default clip */
    /* 0x50c */ struct ASEG *paseg50C;   /* field: SafeHouse port - kind 12's clip */
};
struct ACTOR {
    /* 0x0000 */ char pad0[0x4c0];
    /* 0x04c0 */ struct INTERACT inter;  /* field: SafeHouse port */
    /* 0x09d0 */ char pad9D0[0x1318 - 0x9d0];
    /* 0x1318 */ int n1318;              /* field: SafeHouse port */
};
void StartInteract(struct INTERACT *pinter, int n, struct LO *plo, int jtl) asm("StartInteract__FP5ACTORii3JTL");

// name: SafeHouse port (StartPrizeInteract)
void StartPrizeInteract__FP5ACTORP4ASEGP2LOi(struct ACTOR *pactor, struct ASEG *paseg, struct LO *ploPrize, int n)
{
    if (paseg == 0)
        paseg = pactor->inter.paseg508;
    pactor->inter.paseg50C = paseg;
    StartInteract(&pactor->inter, 12, ploPrize, 0);
    pactor->n1318 = n;
}
