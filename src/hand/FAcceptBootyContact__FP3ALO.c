/* FAcceptBootyContact (vt slot 75): a contact the base accepts (FAbsorbSoWkr) ends a thrown booty's flight
 * (state 5 -> 0). Layout: SafeHouse port (booty.cpp BOOTY). */
struct WKR;
struct BOOTY {
    /* 0x000 */ char pad0[0x184];
    /* 0x184 */ int state;   /* field: SafeHouse port (5: thrown) */
};
int FAbsorbSoWkr(struct BOOTY *pbooty, struct WKR *pwkr) asm("FAbsorbSoWkr__FP2SOP3WKR");
void SetBootyState(struct BOOTY *pbooty, int state) asm("SetBootyState__FP2LOi");

// name: SafeHouse port (FAcceptBootyContact)
int FAcceptBootyContact__FP3ALO(struct BOOTY *pbooty, struct WKR *pwkr)
{
    if (!FAbsorbSoWkr(pbooty, pwkr) || pbooty->state != 5)
        return 0;
    SetBootyState(pbooty, 0);
    return 1;
}
