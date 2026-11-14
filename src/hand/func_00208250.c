/* class: STEPGUARD (CloneStepguard calls it): after a clone, each of its mask kind entries (+0x4D0, 0x20 bytes,
 * +0x4C0 of them; SafeHouse GUARD akinde) fixed up (0x209590), then its three 26-entry KINDE arrays (+0xC10, +0x8D0,
 * +0xA70: 0x208208). */
typedef struct GUARD GUARD;
typedef struct KINDE {           /* a guard kind entry (SafeHouse guardstart.cpp KINDE; 0x10 bytes) */
    /* 0x0 */ int k;             /* 2 / 3: +0x4 is a KIND2 / KIND3 from its slot heap; -1 none */
    /* 0x4 */ union { int oid; void *pk; } u;
    /* 0x8 */ int n8;
    /* 0xc */ int grf;
} KINDE;
typedef struct KINDEM { char ab[0x20]; } KINDEM;   /* a mask's kind entry */
typedef struct STEPGUARD {
    /* 0x000 */ char pad0[0x4c0];
    /* 0x4c0 */ int ckindem;
    /* 0x4c4 */ char pad4c4[0xc];
    /* 0x4d0 */ KINDEM akindem[32];
} STEPGUARD;

void func_00209590(KINDEM *pkindem);
void func_00208208(STEPGUARD *pstepguard, KINDE *akinde);

void func_00208250(STEPGUARD *pstepguard)
{
    int i;

    for (i = 0; i < pstepguard->ckindem; i++) {
        func_00209590(&pstepguard->akindem[i]);
    }
    func_00208208(pstepguard, (KINDE *)((char *)pstepguard + 0xC10));
    func_00208208(pstepguard, (KINDE *)((char *)pstepguard + 0x8D0));
    func_00208208(pstepguard, (KINDE *)((char *)pstepguard + 0xA70));
}
