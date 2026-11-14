/* class: STEPGUARD (InitStepguard calls it): its three 26-entry KINDE arrays (+0xC10, +0x8D0, +0xA70) reset
 * (0x208178). */
typedef struct GUARD GUARD;
typedef struct KINDE {           /* a guard kind entry (SafeHouse guardstart.cpp KINDE; 0x10 bytes) */
    /* 0x0 */ int k;             /* 2 / 3: +0x4 is a KIND2 / KIND3 from its slot heap; -1 none */
    /* 0x4 */ union { int oid; void *pk; } u;
    /* 0x8 */ int n8;
    /* 0xc */ int grf;
} KINDE;

void func_00208178(GUARD *pguard, KINDE *akinde);

void func_002081C8(GUARD *pguard)
{
    func_00208178(pguard, (KINDE *)((char *)pguard + 0xC10));
    func_00208178(pguard, (KINDE *)((char *)pguard + 0x8D0));
    func_00208178(pguard, (KINDE *)((char *)pguard + 0xA70));
}
