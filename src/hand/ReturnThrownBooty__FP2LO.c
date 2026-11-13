/* ReturnThrownBooty (a deferred call): a thrown booty (state 5) goes back to its stand (state 1) when the stand is
 * in the world and active (0x1A61A0), else out (state 0). Layout: SafeHouse port (booty.cpp BOOTY). */
struct LO;
struct BOOTY {
    /* 0x000 */ char pad0[0x158];
    /* 0x158 */ int irec;           /* field: SafeHouse port */
    /* 0x15c */ struct LO *pstand;  /* field: SafeHouse port */
    /* 0x160 */ char pad160[0x184 - 0x160];
    /* 0x184 */ int state;          /* field: SafeHouse port */
};
void SetBootyState__FP2LOi(struct BOOTY *pbooty, int st);
int func_001A61A0(struct LO *plo);   /* SafeHouse: in the world, its root active */

// name: SafeHouse port (ReturnThrownBooty)
void ReturnThrownBooty__FP2LO(struct BOOTY *pbooty)
{
    if (pbooty->state == 5) {
        struct LO *pstand = pbooty->pstand;
        int irec;
        pbooty->pstand = 0;
        irec = pbooty->irec;
        SetBootyState__FP2LOi(pbooty, 0);
        if (pstand != 0 && func_001A61A0(pstand)) {
            pbooty->pstand = pstand;
            pbooty->irec = irec;
            SetBootyState__FP2LOi(pbooty, 1);
        }
    }
}
