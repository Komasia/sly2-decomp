/* class: an object holding a guard (+0xAC) and a KINDE (+0xB0) (the splice method 0x104408: an oid and flags):
 * the entry reset (StopKinde 0x2090D0), then its oid and flags set - not resolved (see 0x20AF88). */
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

void func_0020AF38(GKINDE *p, int oid, int grf)
{
    func_002090D0(&p->kinde, p->pguard);
    p->kinde.u.oid = oid;
    p->kinde.grf = grf;
}
