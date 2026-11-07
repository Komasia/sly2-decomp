typedef int qword __attribute__((mode(TI)));
struct E { char pad[0x80]; qword v80; char pad2[0x20]; char subB0[0x10]; int nC0; };
struct P { char pad[0x58]; int n58; char pad2[0xE8 - 0x5C]; struct E *pe; char pad3[0x138 - 0xEC]; int n138; };
extern qword D_002A2DD0;
int func_0011D4D0(float, float, float);
qword ProjectCnstr__FP6CNSTRSP2XFG9VU_VECTOR(void *p, int n, qword v);
void AccelAloPos__FP3ALOG9VU_VECTOR(struct P *p, qword v);
void ApplyAloWater__FP3ALO(struct P *p);
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline int FNear(qword a, qword b)
{
    return func_0011D4D0(X(a), X(b), 0.0001f) && func_0011D4D0(Y(a), Y(b), 0.0001f) && func_0011D4D0(Z(a), Z(b), 0.0001f);
}
// name: SafeHouse port (ApplyAloGravity)
void ApplyAloGravity__FP3ALO(struct P *p)
{
    int fUpd = 0;
    int fNear = FNear(D_002A2DD0, p->pe->v80);
    if (!fNear) fUpd = p->pe->nC0 != 3;
    if (fUpd) AccelAloPos__FP3ALOG9VU_VECTOR(p, ProjectCnstr__FP6CNSTRSP2XFG9VU_VECTOR(p->pe->subB0, p->n58, p->pe->v80));
    if (p->n138) ApplyAloWater__FP3ALO(p);
}
