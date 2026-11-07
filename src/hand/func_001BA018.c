typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x30]; qword q30; char pad1[0xA0 - 0x40]; int nA0; };
struct L { char pad[0x30]; qword q30; };
struct S { char pad[0x1020]; void *p1020; char pad1[0x1030 - 0x1024]; void *p1030; struct T *p1034;
           char pad2[0x1040 - 0x1038]; qword q1040; char pad3[0x1060 - 0x1050]; int n1060; int pad4[2]; int n106C; };
extern char D_002C0A50[];
void PostStepguardLoad__FP9STEPGUARD(struct S *p);
void BindLoParts__FP3ALOiPv(struct S *p, int n, void *pv);
float *PeventLaunch__FP5KINDEi(void *p, int n);
void CalculateAsegMatrices__FP4ASEGP3ALOP2XFT2ffP7MATRIX4T6(void *p, struct S *ps, void *p1, int n, struct L *pl, int m, float a, float b);
void SetSoMass__FP2SOf(struct S *p, float g);
void func_001BA018(struct S *p)
{
    struct L l;
    qword a, b, d;
    float *pg;
    PostStepguardLoad__FP9STEPGUARD(p);
    BindLoParts__FP3ALOiPv(p, 3, D_002C0A50);
    pg = PeventLaunch__FP5KINDEi(p->p1020, 0x5DB);
    CalculateAsegMatrices__FP4ASEGP3ALOP2XFT2ffP7MATRIX4T6(p->p1020, p, p->p1030, p->p1034->nA0, &l, 0, *pg, 1.0f);
    a = l.q30;
    b = p->p1034->q30;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    p->n1060 = 0;
    p->q1040 = d;
    p->n106C = 1;
    SetSoMass__FP2SOf(p, 0.25f);
}
