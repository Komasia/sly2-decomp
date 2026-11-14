/* class: an object holding a guard (+0xAC) and a KINDE (+0xB0) (the splice method 0x1044B0): as 0x20AF38, then the
 * entry resolved (ResolveKinde). */
typedef struct GUARD GUARD;
typedef struct KINDE {           /* a guard kind entry (SafeHouse guardstart.cpp KINDE; 0x10 bytes) */
    /* 0x0 */ int k;             /* 2 / 3: +0x4 is a KIND2 / KIND3 from its slot heap; -1 none */
    /* 0x4 */ union { int oid; void *pk; } u;
    /* 0x8 */ int n8;
    /* 0xc */ int grf;
} KINDE;
typedef struct GKINDE {         /* an object with a guard (+0xAC) and a KINDE (+0xB0) */
    /* 0x00 */ char pad0[0xac];
    /* 0xac */ GUARD *pguard;
    /* 0xb0 */ KINDE kinde;
} GKINDE;

void func_002090D0(KINDE *pkinde, GUARD *pguard);
void ResolveKinde__FP5KINDEP5GUARD(KINDE *pkinde, GUARD *pguard);

void func_0020AF88(GKINDE *p, int oid, int grf)
{
    KINDE *pkinde = &p->kinde;

    func_002090D0(pkinde, p->pguard);
    p->kinde.u.oid = oid;
    p->kinde.grf = grf;
    ResolveKinde__FP5KINDEP5GUARD(pkinde, p->pguard);
}
