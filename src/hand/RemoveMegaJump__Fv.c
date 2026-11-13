/* RemoveMegaJump (a reload of the same world with the transition's flag 0x40): the current player's (D_002E1E40)
 * Mega Jump (ability 0x1F) slot emptied, and the gadget no longer owned (0x1DAF38). Source: SafeHouse port
 * (gadget.cpp). */
struct ACTOR;
extern struct ACTOR *D_002E1E40;   /* the current player */
int func_00141E78(struct ACTOR *pactor, int id);   /* the slot of an ability (-1 none) */
void SetActorAbilitySlot__FP5ACTORii(struct ACTOR *pactor, int islot, int id);
void func_001DAF38(int id, int fOwned);

// name: SafeHouse port (RemoveMegaJump)
void RemoveMegaJump__Fv(void)
{
    if (D_002E1E40 != 0) {
        int islot = func_00141E78(D_002E1E40, 0x1F);
        if (islot != -1)
            SetActorAbilitySlot__FP5ACTORii(D_002E1E40, islot, -1);
        func_001DAF38(0x1F, 0);
    }
}
