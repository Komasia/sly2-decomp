/* func_00208538 (0x208538): GUARD option setter (EOPID 260, option 386): its target (+0x390); the getter reads the
 * pursued object +0x38C. */
struct GUARD {
    /* 0x000 */ char pad0[0x390];
    /* 0x390 */ int ploTarget;   /* field: SafeHouse port */
};

void func_00208538(struct GUARD *pguard, int plo)
{
    pguard->ploTarget = plo;
}
