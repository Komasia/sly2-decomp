/* class: KINDE (SafeHouse guardstart.cpp StopKinde: "0x2090D0 resets the entry's kind payload"): a kind-2 / kind-3
 * payload returned to its slot heap (0x20C030 / 0x20CA20), then no kind and no oid. */
typedef struct GUARD GUARD;
typedef struct KINDE {           /* a guard kind entry (SafeHouse guardstart.cpp KINDE; 0x10 bytes) */
    /* 0x0 */ int k;             /* 2 / 3: +0x4 is a KIND2 / KIND3 from its slot heap; -1 none */
    /* 0x4 */ union { int oid; void *pk; } u;
    /* 0x8 */ int n8;
    /* 0xc */ int grf;
} KINDE;

void func_0020C030(void *pk2);
void func_0020CA20(void *pk3);

void func_002090D0(KINDE *pkinde, GUARD *pguard)
{
    if (pkinde->k != 2) {
        if (pkinde->k == 3) {
            func_0020CA20(pkinde->u.pk);
            pkinde->u.pk = 0;
        }
    } else {
        func_0020C030(pkinde->u.pk);
        pkinde->u.pk = 0;
    }
    pkinde->u.oid = -1;
    pkinde->k = -1;
}
