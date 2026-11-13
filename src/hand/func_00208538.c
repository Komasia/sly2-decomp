/* class: GUARD (SafeHouse guardstart.cpp: EOPID 260, option 386 - the setter writes +0x390, the getter reads the
 * pursued object +0x38C). */
struct GUARD {
    /* 0x000 */ char pad0[0x390];
    /* 0x390 */ int n390;
};

void func_00208538(struct GUARD *pguard, int n)
{
    pguard->n390 = n;
}
