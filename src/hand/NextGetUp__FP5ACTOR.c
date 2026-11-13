/* NextGetUp (a damage state's next step): with hit points left (*+0x10) the actor gets up (damage state 0), else
 * state 8. Source: SafeHouse port (damage.cpp). */
struct ACTOR {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ int *pcount;   /* field: SafeHouse port (Dmg(pa).pcount) */
};
void SetDamageState__FP5ACTORi(struct ACTOR *pactor, int st);

// name: SafeHouse port (NextGetUp, damage.cpp)
void NextGetUp__FP5ACTOR(struct ACTOR *pactor)
{
    if (*pactor->pcount > 0) {
        SetDamageState__FP5ACTORi(pactor, 0);
        return;
    }
    SetDamageState__FP5ACTORi(pactor, 8);
}
