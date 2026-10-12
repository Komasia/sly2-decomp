/* wip: 17 diffs - v1/a0 register swap for p->pq loads around c/q240 store, and union sqc2 of qmtc2'd scalar scheduled earlier than target. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct E { float a; float b; float c; float d; };
struct Q0 { char pad[0x40]; char a40[1]; };
struct Q { struct Q0 *p0; char pad[0x1C - 4]; int c; char pad2[0x78 - 0x20]; char a78[4]; void *p7C; char pad3[0x90 - 0x80]; char a90[4]; char *p94; };
struct M { char pad[0x1C]; int n1C; char pad2[0x78 - 0x20]; int n78; };
struct S {
    char pad0[0x28]; unsigned long fl28; char pad1[0x60 - 0x30]; void *p60; char pad2[0xE0 - 0x64]; int nE0; char *pE4;
    char pad3[0x210 - 0xE8]; float f210; int n214; char *p218; char *p21C; char pad4[0x240 - 0x220]; qword q240;
    char pad5[0x258 - 0x250]; struct Q *pq;
};
extern float D_002A85F0;
extern qword D_002A2DC0;
extern qword D_002A2DD0;
void func_001F2BA8(struct S *p);
void func_001F2B20(struct S *p);
int func_00132B10(struct S *p, int n);
void func_001F70C0(struct M *m, void *p, int k, struct Q *q);
void func_001F6C08(struct Q *q);
void func_001664A0(void *a, void *b, void *c);

void func_00203AF0(struct S *p, struct M *m)
{
    int n, fl, i, c;
    float mn;
    U u;
    qword r;
    if ((int)(p->fl28 >> 60) & 1)
        func_001F2BA8(p);
    n = p->nE0;
    p->nE0 = n + 1;
    fl = 0;
    p->pq = (struct Q *)(p->pE4 + n * 0xB0);
    if (!func_00132B10(p, 0x34))
        fl = m->n1C == m->n78;
    func_001F70C0(m, p->p60, !fl ? 2 : 3, p->pq);
    func_001F6C08(p->pq);
    mn = D_002A85F0;
    for (i = 0; i < p->pq->c; i++) {
        float e = ((struct E *)p->pq->p7C)[i].c;
        mn = (e > mn) ? mn : e;
    }
    p->f210 = mn;
    c = p->pq->c;
    p->pq->c = c + 2;
    ((qword *)p->pq->p7C)[c] = p->q240;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(p->n214));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(p->q240), "j"(D_002A2DC0), "j"(u.q));
    ((qword *)p->pq->p7C)[c + 1] = r;
    if (fl)
        ((qword *)p->pq->p7C)[c + 2] = D_002A2DD0;
    func_001664A0(p->pq->p0->a40, p->pq->a78, p->pq->a90);
    p->p218 = p->pq->p94 + c * 16;
    p->p21C = p->pq->p94 + (c * 16 + 0x10);
    if ((int)(p->fl28 >> 60) & 1)
        func_001F2B20(p);
}
