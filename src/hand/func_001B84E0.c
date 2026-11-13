/* class: MURRAY (SafeHouse gang.cpp, orig 0x001B84E0): while a punch plays (+0x190C) or is set (+0x1810), whether the
 * next punch may start (+0x1820); otherwise 1. */
struct ASEGA;
struct MURRAY {
    /* 0x0000 */ char pad0[0x1810];
    /* 0x1810 */ int nPunch;              /* field: SafeHouse port (n1810) - the punch, -1 none */
    /* 0x1814 */ char pad1814[0x1820 - 0x1814];
    /* 0x1820 */ int fPunchNext;          /* field: SafeHouse port (f1820) - the next punch may start */
    /* 0x1824 */ char pad1824[0x190c - 0x1824];
    /* 0x190c */ struct ASEGA *pasegaPunch;   /* field: SafeHouse port (pasega190C) - a punch left playing */
};

int func_001B84E0(struct MURRAY *pmurray)
{
    if (pmurray->pasegaPunch != 0 || pmurray->nPunch != -1) {
        return pmurray->fPunchNext;
    }
    return 1;
}
