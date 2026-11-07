typedef int qword __attribute__((mode(TI)));
typedef struct VTE { short d; short pad; void (*pfn)(); } VTE;
typedef union U { int i; float f; } U;
typedef struct Q { char pad[0xC]; VTE *vt; } Q;
typedef struct E { char pad0[0xC]; struct Q *pq; char pad[0x30]; } E;
typedef struct X {
    char pad0[0xC];
    Q *pq;
    char pad10[0x80 - 0x10];
    qword x80;
    char pad90[0x88 - 0x90 + 0x10];
} X;
typedef struct P {
    char pad0[0xC];
    VTE *vt;
    char pad10[0xDF0 - 0x10];
    char xDF0[0xF50 - 0xDF0];
    char xF50[0x13D0 - 0xF50];
    int x13D0;
    int pad13D4;
    int x13D8;
    char pad13DC[0x13E4 - 0x13DC];
    char x13E4[0x1840 - 0x13E4];
    int x1840;
    char pad1844[0x1908 - 0x1844];
    int x1908;
} P;
extern "C" float D_002C3C60[];
extern "C" float D_002C0A38;
extern "C" char g_sw[];
extern "C" void OnStepXpNew(P *p, X *px, int i) asm("OnStepXpNew__FP3ALOP2XPi");
extern "C" void AdjustDamageXp(void *p, X *px, int i) asm("AdjustDamageXp__FP5ACTORP2XP");
extern "C" void AdjustClimbXp(void *p, X *px, int i) asm("AdjustClimbXp__FP2XPPv");
extern "C" qword func_0011F198(qword a, qword b);
extern "C" int PxpCloneList(void *g, X *px) asm("PxpCloneList__FP2XPPv");
extern "C" void PrependXpList(void *g, int r, void *p) asm("PrependXpList__FP2XPPP2XPPv");

// name: SafeHouse port (OnMurrayXpNew)
extern "C" void OnMurrayXpNew__FP3ALOP2XPi(P *p, X *px, int i)
{
    int n;
    OnStepXpNew(p, px, i);
    switch (p->x13D0) {
    case 14:
        AdjustDamageXp(p->xDF0, px, i);
        break;
    case 12:
        n = p->x1840;
        if (n == 1) {
            Q *pq = *(Q **)((char *)px + ((n-i)<<6) + 0xC);
            if (((int (*)(void *))pq->vt[62].pfn)((char *)pq + pq->vt[62].d)) {
                if (*(float *)((char *)px + 0x88) < 0.7f) {
                    qword v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);
                    qword r = func_0011F198(v, px->x80);
                    float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(r));
                    int f = g < D_002C0A38;
                    if (f) p->x1908 = n;
                }
            }
        }
        break;
    case 3:
        if (p->x13D8 == 1) {
            if (D_002C3C60[i] * *(float *)((char *)px + 0x88) > 0.7f) {
                PrependXpList(g_sw, PxpCloneList(g_sw, px), p->x13E4);
            }
        }
        break;
    case 20:
        AdjustClimbXp(p->xF50, px, i);
        break;
    }
}
