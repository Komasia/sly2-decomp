/* class: GUARD (SafeHouse guardstart.cpp: EOPID 272 -> 0x208B30, the immediate ones +0x3C0 cleared). */
struct GUARD {
    /* 0x000 */ char pad0[0x3c0];
    /* 0x3c0 */ int grfImmediate;
};

void func_00208B30(struct GUARD *pguard)
{
    pguard->grfImmediate = 0;
}
