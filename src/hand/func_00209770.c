/* func_00209770 (0x209770): MOVEREF clone (CloneStepguard): the move reference belongs to the new guard. */
struct GUARD;
struct MOVEREF {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ struct GUARD *pguard;   /* field: SafeHouse port */
};

void func_00209770(struct MOVEREF *pmove, struct GUARD *pguard)
{
    pmove->pguard = pguard;
}
