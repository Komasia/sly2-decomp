/* v4 (Claude agent lane G, 2026-10-24): aligned 12 (v3 is 10), but the layout is now right: bltz with the then-path first, thanks to 'for (i = a->n488, n = 0; ...)' (the else arm must not START by setting n, or jump.c hoists n = n3D8 above the branch). Left: the Count param copy lands in a0, not a1, because arg0 of func_001A6F00 reuses it; the target reloads p->p10 there. */
/* v3 (Claude agent, 2026-10-17): aligned 19 -> 10. Block-scoped `struct A *b = p->p10;` passed to Count and reused for the v3E0 argument (target keeps the pointer in a1 for both). Left: target loads p10 into v0 and n3D8 into a2 then copies them to a1/s0 (bltz with copies in the slots); ours loads straight into a1/s0 (bgez). */
/* v2 (Claude agent, 2026-10-17): aligned 22 -> 19. Count() writes the result into one variable n in both branches (`if (n3D8 >= 0) n = n3D8; else {n = 0; loop; n = (n+1)/2;} return n;`) so the accumulator shares s0 with the result, and the 1A6F00 call is its own `qword v = ...;` statement (s2 = hi of D_002DE578). Left: target loads n3D8 into a2 and copies to s0 in the bltz slot (ours bgez with n loaded straight into s0), so the then-path layout differs. */
typedef int qword __attribute__((mode(TI)));
struct G;
extern struct G D_003DD490;
extern char D_002DEB30[];
extern char D_002DE578[];
struct E { int n0; int pad[2]; int nC; };
struct A {
    char pad[0xEC]; void *pEC; char padF0[0x330-0xF0]; int n330; char pad2[0x3D8 - 0x334]; int n3D8; char pad3[4]; qword v3E0; int n3F0;
    char pad4[0x404 - 0x3F4]; struct E ae[(0x484 - 0x404) / 16]; int n484; int n488;
    char pad5[0xF64 - 0x48C]; void *pF64;
};
struct S { char pad[0x10]; struct A *p10; char pad2[0x2C]; int *p40; char pad3[0xC]; void *p50; char pad4[8]; int mask5C; };
int func_001F78A0(int mask);
void func_00179328(struct S *p);
void *func_001C4840(struct G *g);
void func_001619A0(void *a, int n, struct A *p);
qword func_001A6F00(struct A *source, void *target, qword v);
void func_00154E10(void *a, qword v, int n, int m, struct A *p);
void func_00134320(struct G *g, struct A *p);
void func_00153FF8(void *p);
static inline int Count(struct A *a) {
    int n, i;
    if (a->n3D8 >= 0) {
        n = a->n3D8;
    } else {
        for (i = a->n488, n = 0; i < a->n484; i++) {
            struct E *e = &a->ae[i];
            if (e->n0 == 0x2B3) n += e->nC;
        }
        n = (n + 1) / 2;
    }
    return n;
}
void func_00179898(struct S *p) {
    int n;
    struct A *a;
    int *pe = (int *)((char *)p->p10 + (func_001F78A0(p->mask5C) * 16 + 0xC10));
    p->p40 = pe;
    if (*pe == -1) p->p40 = 0;
    func_00179328(p);
    a = p->p10;
    if (a->n330 == 0) {
        a->n330 = 1;
        if (p->p50 == func_001C4840(&D_003DD490))
            func_001619A0(D_002DEB30, 0x18, p->p10);
        else
            func_001619A0(D_002DEB30, 0x17, p->p10);
        n = Count(p->p10);
        {
            qword v = func_001A6F00(p->p10, 0, p->p10->v3E0);
            func_00154E10(D_002DE578, v, n, p->p10->n3F0, p->p10);
        }
        func_00134320(&D_003DD490, p->p10);
        func_00153FF8(p->p10->pF64);
    }
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_int[(sizeof(int)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_E[(sizeof(struct E)==16)?1:-1];
typedef char layout_A_prefix[(sizeof(struct A)==0xF70)?1:-1];
typedef char layout_S_prefix[(sizeof(struct S)==0x60)?1:-1];
typedef char layout_A_align[(__alignof__(struct A)==16)?1:-1];
typedef char layout_A_pEC[((unsigned)&((struct A*)0)->pEC==0xec)?1:-1];
typedef char layout_A_n330[((unsigned)&((struct A*)0)->n330==0x330)?1:-1];
typedef char layout_A_n3D8[((unsigned)&((struct A*)0)->n3D8==0x3d8)?1:-1];
typedef char layout_A_v3E0[((unsigned)&((struct A*)0)->v3E0==0x3e0)?1:-1];
typedef char layout_A_n3F0[((unsigned)&((struct A*)0)->n3F0==0x3f0)?1:-1];
typedef char layout_A_ae[((unsigned)&((struct A*)0)->ae==0x404)?1:-1];
typedef char layout_A_n484[((unsigned)&((struct A*)0)->n484==0x484)?1:-1];
typedef char layout_A_n488[((unsigned)&((struct A*)0)->n488==0x488)?1:-1];
typedef char layout_A_pF64[((unsigned)&((struct A*)0)->pF64==0xf64)?1:-1];
typedef char layout_S_p10[((unsigned)&((struct S*)0)->p10==0x10)?1:-1];
typedef char layout_S_p40[((unsigned)&((struct S*)0)->p40==0x40)?1:-1];
typedef char layout_S_p50[((unsigned)&((struct S*)0)->p50==0x50)?1:-1];
typedef char layout_S_mask5C[((unsigned)&((struct S*)0)->mask5C==0x5c)?1:-1];
typedef char layout_E_n0[((unsigned)&((struct E*)0)->n0==0x0)?1:-1];
typedef char layout_E_nC[((unsigned)&((struct E*)0)->nC==0xc)?1:-1];
typedef char layout_A_entry_capacity[(sizeof(((struct A*)0)->ae)/sizeof(struct E)==8)?1:-1];
