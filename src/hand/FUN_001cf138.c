/* FUN_001cf138 (name taken from a Sly 1 address): a jump target's score - the two partial scores added, and 1000
 * worse when the target is the object of the state just left (SafeHouse port, actor.h JUMP +0xBC ploLeft). */
struct LO;
struct JUMP {
    /* 0x00 */ char pad0[0xbc];
    /* 0xbc */ struct LO *ploLeft;   /* field: SafeHouse port */
};

extern float D_002BF900;   /* 1000.0f */

float FUN_001cf138(struct JUMP *pjump, struct LO *plo, float g1, float g2)
{
    float g = g1 + g2;
    if (plo == pjump->ploLeft)
        g += D_002BF900;
    return g;
}
