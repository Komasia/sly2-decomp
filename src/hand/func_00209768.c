/* func_00209768 (0x209768): MOVEREF init (InitStepguard): the move reference belongs to the guard. */
struct GUARD;
struct MOVEREF {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ struct GUARD *pguard;   /* field: SafeHouse port */
};

void func_00209768(struct MOVEREF *pmove, struct GUARD *pguard)
{
    pmove->pguard = pguard;
}
