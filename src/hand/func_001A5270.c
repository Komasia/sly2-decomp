/* InitLo (0x1A5270): the LO's init (vt slot 7): defaults in its flags word (+0x28: bits 48..51 0xF, the activation
 * kind (bits 52..55) 2, bits 40..47 0xFF), no radius limit (+0x38 1e10); a child takes its parent's root id (+0x14)
 * and in-world bit (60), a root gets its own LOROOT (func_001A53A0) and is in the world; +0x40 = 0x21; the namespace
 * row (+0x3C) from the parent, else D_003E139C; then the LO is linked before the parent's first removed child
 * (func_001A5448). SafeHouse activate.cpp / brx.cpp. */
struct S {
    int x0, x4, x8, xC;
    struct S *x10;
    int x14;
    char pad[0x10];
    union { unsigned long u; struct { unsigned long f0 : 40; unsigned long b40 : 8; unsigned long f48 : 4; long st : 4; unsigned long f56 : 4; unsigned long f60 : 1; unsigned long f61 : 3; } b; } x28;
    int x30, x34;
    float x38;
    int x3C;
    int x40;
};
extern int g_ploNsRowDefault __asm__("D_003E139C");
void func_001A53A0(struct S *s);
void func_001A5448(struct S *psoParent, void **ppdl, void ***ppploFirstRemoved);
void InsertDlEntryBefore__FP2DLPvT1(void *a, void *b, struct S *s);
void InitLo__FP2LO(struct S *plo)
{
    void *pdl;
    void **pploFirstRemoved;
    plo->x28.b.f48 = 0xF;
    plo->x38 = 1e10f;
    plo->x28.b.st = 2;
    plo->x28.b.b40 = 0xFF;
    if (plo->x10) {
        plo->x14 = plo->x10->x14;
        plo->x28.b.f60 = (int)(plo->x10->x28.u >> 60);
    } else {
        func_001A53A0(plo);
        plo->x28.b.f60 = 1;
    }
    plo->x40 = 0x21;
    plo->x3C = plo->x10 ? plo->x10->x3C : g_ploNsRowDefault;
    func_001A5448(plo->x10, &pdl, &pploFirstRemoved);
    InsertDlEntryBefore__FP2DLPvT1(pdl, *pploFirstRemoved, plo);
}
