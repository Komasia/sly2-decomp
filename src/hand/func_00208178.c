/* class: GUARD (SafeHouse guardstart.cpp: the guard's 26-entry KINDE arrays, SetArrayKindes): each entry of one
 * array reset (StopKinde 0x2090D0). */
typedef struct GUARD GUARD;
typedef struct KINDE {           /* a guard kind entry (SafeHouse guardstart.cpp KINDE; 0x10 bytes) */
    /* 0x0 */ int k;             /* 2 / 3: +0x4 is a KIND2 / KIND3 from its slot heap; -1 none */
    /* 0x4 */ union { int oid; void *pk; } u;
    /* 0x8 */ int n8;
    /* 0xc */ int grf;
} KINDE;

void func_002090D0(KINDE *pkinde, GUARD *pguard);

void func_00208178(GUARD *pguard, KINDE *akinde)
{
    int i;

    for (i = 0; i < 26; i++) {
        func_002090D0(&akinde[i], pguard);
    }
}
