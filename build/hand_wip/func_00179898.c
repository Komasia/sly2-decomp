typedef int qword __attribute__((mode(TI)));
struct G;
extern struct G D_003DD490;
extern char D_002DEB30[];
extern char D_002DE578[];
struct E { int n0; int pad[2]; int nC; };
struct A {
    char pad[0x330]; int n330; char pad2[0x3D8 - 0x334]; int n3D8; char pad3[4]; qword v3E0; int n3F0;
    char pad4[0x404 - 0x3F4]; struct E ae[(0x484 - 0x404) / 16]; int n484; int n488;
    char pad5[0xF64 - 0x48C]; void *pF64;
};
struct S { char pad[0x10]; struct A *p10; char pad2[0x2C]; int *p40; char pad3[0xC]; void *p50; char pad4[8]; void *p5C; };
int func_001F78A0(void *p);
void func_00179328(struct S *p);
void *func_001C4840(struct G *g);
void func_001619A0(void *a, int n, struct A *p);
qword func_001A6F00(struct A *p, int n, qword v);
void func_00154E10(void *a, qword v, int n, int m, struct A *p);
void func_00134320(struct G *g, struct A *p);
void func_00153FF8(void *p);
static inline int Count(struct A *a) {
    int n, i;
    if (a->n3D8 >= 0) return a->n3D8;
    n = 0;
    for (i = a->n488; i < a->n484; i++) {
        struct E *e = &a->ae[i];
        if (e->n0 == 0x2B3) n += e->nC;
    }
    return (n + 1) / 2;
}
void func_00179898(struct S *p) {
    int n;
    struct A *a;
    struct A *b;
    int *pe = (int *)((char *)p->p10 + (func_001F78A0(p->p5C) * 16 + 0xC10));
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
        func_00154E10(D_002DE578, func_001A6F00(p->p10, 0, p->p10->v3E0), n, p->p10->n3F0, p->p10);
        func_00134320(&D_003DD490, p->p10);
        func_00153FF8(p->p10->pF64);
    }
}
