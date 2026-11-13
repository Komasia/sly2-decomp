/* class: CID_64, the carryables (SafeHouse carry.cpp: its kind +0x15C is 0xB). */
struct CARRY {
    /* 0x000 */ char pad0[0x15c];
    /* 0x15c */ int kind;
};

int func_00224688(struct CARRY *pcarry)
{
    return pcarry->kind == 0xB;
}
