/* PoxAddSw: a new overlap record (from the world's slot heap +0x3CF8) at the head of an object's list (OXA +0x64),
 * for the other object. Layout: SafeHouse port (bbmark.cpp OX / OXA). */
struct SO;
struct SW;
struct OX {
    /* 0x0 */ int n0;
    /* 0x4 */ struct OX *poxNext;     /* field: SafeHouse port */
    /* 0x8 */ int n8;
    /* 0xc */ struct SO *psoOther;    /* field: SafeHouse port */
};
struct OXA {
    /* 0x00 */ char pad0[0x60];
    /* 0x60 */ struct SO *pso;        /* field: SafeHouse port */
    /* 0x64 */ struct OX *pox;        /* field: SafeHouse port - the list */
};
void *func_0011CCC0(void *pslotheap);   /* a slot heap's new slot */

// name: SafeHouse port (PoxAddSw)
struct OX *PoxAddSw__FP2SWP3OXAT1(struct SW *psw, struct OXA *poxa, struct OXA *poxaOther)
{
    struct OX *pox = (struct OX *)func_0011CCC0((char *)psw + 0x3cf8);
    pox->psoOther = poxaOther->pso;
    pox->poxNext = poxa->pox;
    poxa->pox = pox;
    return pox;
}
