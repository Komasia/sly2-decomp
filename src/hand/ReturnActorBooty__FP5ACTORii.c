/* ReturnActorBooty: the booty an actor carries (+0x11A8) put back on its stand (state 0), after the save of the move (kind 1).
 * Layout: SafeHouse port (booty.h). */
struct LO;
struct ACTOR {
    /* 0x0000 */ char pad0[0x11a8];
    /* 0x11a8 */ struct LO *pbooty;   /* field: SafeHouse port - the carried booty */
};
void SaveBootyMove(struct ACTOR *pactor, int k, struct LO *pstand) asm("SaveBootyMove__FP5ACTORiP2LO");
void SetBootyState(struct LO *pbooty, int state) asm("SetBootyState__FP2LOi");

// name: SafeHouse port (ReturnActorBooty)
void ReturnActorBooty__FP5ACTORii(struct ACTOR *pactor, int a1, int a2)
{
    if (pactor->pbooty) {
        SaveBootyMove(pactor, 1, 0);
        SetBootyState(pactor->pbooty, 0);
    }
}
