/* class: GUARD (SafeHouse guardstart.cpp: the getter of the detector sub-object +0xF64, for the options' binds). */
struct DETECTOR;
struct GUARD {
    /* 0x000 */ char pad0[0xf64];
    /* 0xf64 */ struct DETECTOR *pdet;   /* field: SafeHouse port */
};

struct DETECTOR *func_00206378(struct GUARD *pguard)
{
    return pguard->pdet;
}
