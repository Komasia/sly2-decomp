/* class: the safe house, class 0x46: add an action entry {state, buttons, target} (option 1338, given by the splice
 * method func_0010F590) to the list at +0x190 (at most 12, count at +0x18C). UpdateSafeHouse (0x1D72A8) runs the
 * entry of the current state when its buttons are pressed: target 0x378 opens the shop, else a script starts
 * (SafeHouse po.cpp UpdateSafeHouse: "option 1338: {state, buttons, target}").
 * name: was AddStepguardEffect__FP9STEPGUARD3OID3ZPK, a bad Sly 1 shape match (it sits in the safe house module
 * between SetSafeHouseState 0x1D7480 and the state stepper 0x1D77D0, and its object is the safe house). */
typedef int OID;
struct SAFEHOUSEACTION {
    /* 0x0 */ OID oidState;     /* the state machine state it applies to */
    /* 0x4 */ int grfbtn;       /* the buttons (the splice argument of type 0x103C) */
    /* 0x8 */ OID oidTarget;    /* 0x378: the shop; -1: none; else a script */
};
struct SAFEHOUSE {
    /* 0x000 */ char pad0[0x18C];
    /* 0x18C */ unsigned int caction;
    /* 0x190 */ struct SAFEHOUSEACTION aaction[12];
};

void func_001D7748(struct SAFEHOUSE *psh, OID oidState, int grfbtn, OID oidTarget)
{
    unsigned int iaction = psh->caction;
    if (iaction < 12) {
        struct SAFEHOUSEACTION *paction;
        psh->caction = iaction + 1;
        paction = &psh->aaction[iaction];
        paction->oidState = oidState;
        paction->grfbtn = grfbtn;
        paction->oidTarget = oidTarget;
    }
}
