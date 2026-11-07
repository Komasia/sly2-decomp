struct VTE { short d; short pad; void (*pf)(); };
struct LO { char pad[0xC]; struct VTE *vt; };
struct S {
    char pad[0xC]; struct VTE *vt;
    char p0[0x180 - 0x10]; int x180; float x184; int p188[2]; struct LO *x190; int x194; int p198; void *x19C; int p1A0; int x1A4;
    char p1[0x1F4 - 0x1A8]; void *x1F4; int p1F8; void *x1FC; int x200; int p204[2]; void *a20C[6];
};
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern char D_003DD040[];
extern char g_sw[];
void StopDialog__FP8SOUNDMGR(void *p);
void StopScptImpl__FP2LO(void *p);
void SetVaultSub__FP2LOi(struct S *p, int n);
void func_0020F160(void *p);
void func_001DAF38(int n, int f);
int PsndStartDialog__FP8SOUNDMGRii(void *p, void *q, int f);
void func_0020F198(void *p);
void func_0020F128(void *p);
void func_0020F1A8(void *p);
void StartScptImpl__FP2LOi(void *p, struct LO *q);
// name: SafeHouse port (SetVaultState)
void SetVaultState__FP2LOi(struct S *p, int n)
{
    void *pv;
    if (n == p->x180) return;
    if (p->x1A4) {
        StopDialog__FP8SOUNDMGR(D_003DD040);
        p->x1A4 = 0;
    }
    if (p->x19C)
        StopScptImpl__FP2LO(p->x19C);
    switch (p->x180) {
    case 2:
        SetVaultSub__FP2LOi(p, -1);
        func_0020F160(g_sw);
        break;
    case 3:
        if (p->x200 != -1)
            func_001DAF38(p->x200, 1);
        if (p->x1FC)
            p->x1A4 = PsndStartDialog__FP8SOUNDMGRii(D_003DD040, p->x1FC, 1);
        break;
    case 0:
        if (p->x190)
            func_0020F198(g_sw);
        break;
    }
    p->x180 = n;
    p->x184 = g_clock.t;
    switch (n) {
    case -1:
        return;
    case 2:
        p->x194 = 5;
        SetVaultSub__FP2LOi(p, 1);
        func_0020F128(g_sw);
        if (p->x1F4)
            p->x1A4 = PsndStartDialog__FP8SOUNDMGRii(D_003DD040, p->x1F4, 0);
        break;
    case 1:
        ((void (*)(void *, int))p->vt[79].pf)((char *)p + p->vt[79].d, 1);
        break;
    case 0:
    case 5: {
        struct LO *q = p->x190;
        if (q) {
            ((void (*)(void *, int))q->vt[79].pf)((char *)q + q->vt[79].d, 1);
            p->x190 = 0;
            func_0020F1A8(g_sw);
        }
        break;
    }
    }
    pv = p->a20C[p->x180];
    p->x19C = pv;
    if (pv)
        StartScptImpl__FP2LOi(pv, p->x190);
}
