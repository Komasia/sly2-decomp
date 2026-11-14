/* class: GUARD (SafeHouse guardstart.cpp: the guard's 26-entry KINDE arrays): each entry of one array resolved
 * (ResolveKinde). */
typedef struct GUARD GUARD;
typedef struct KINDE {           /* a guard kind entry (SafeHouse guardstart.cpp KINDE; 0x10 bytes) */
    /* 0x0 */ int k;             /* 2 / 3: +0x4 is a KIND2 / KIND3 from its slot heap; -1 none */
    /* 0x4 */ union { int oid; void *pk; } u;
    /* 0x8 */ int n8;
    /* 0xc */ int grf;
} KINDE;

void ResolveKinde__FP5KINDEP5GUARD(KINDE *pkinde, GUARD *pguard);

void func_002080A0(GUARD *pguard, KINDE *akinde)
{
    int i;

    for (i = 0; i < 26; i++) {
        ResolveKinde__FP5KINDEP5GUARD(&akinde[i], pguard);
    }
}
