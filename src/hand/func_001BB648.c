typedef int qword __attribute__((mode(TI)));
typedef struct VTE { short d; short pad; void (*pfn)(); } VTE;
typedef struct SO { char pad[0xC]; VTE *vt; } SO;
typedef struct I { int k; int v; } I;
typedef struct E { int id; int n; int c; I *a; } E;
typedef struct MSG { int a; SO *ps; char pad[0x38]; } MSG;
typedef struct P {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x158 - 0x10];
    int x158;
    char pad15C[0x168 - 0x15C];
    int x168;
} P;
extern char g_sw[];
extern char g_cm[];
extern char g_joy[];
extern char D_002DE578[];
extern char g_game[];
SO *func_0015E938(void *g, int k, int v, P *p);
void ShowAloGlobs__FP3ALOi(P *p, int v);
void func_001F69F8(P *p, int v);
void SetAloSoesByTag__FP3ALOi(P *p, int v);
void func_001F6B48(P *p, int v);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int k);
void JoltCm__FP2CMi(void *g, int v);
void TriggerJoyRumbleRumk__FP3JOY4RUMKf(void *g, int v, float f);
qword func_001A62E8(void *p);
void DropPickups__FP6VECTORG9VU_VECTORiiP2LO(void *g, qword q, int v, int a, P *p);
void ApplyCheckpointTasks__FP2SWiP2LOPv(void *g, int k, int v, P *p);

// name: SafeHouse port (RunItems)
void RunItems__FP2LOP3BRK(P *p, E *pe)
{
    int i;
    SO *psPrev = 0;
    for (i = 0; i < pe->c; i++) {
        I *pi = &pe->a[i];
        SO *ps;
        if ((p->x158 > 0 || pe->n <= 0) && ((0x3F >> pi->k) & 1)) continue;
        ps = 0;
        if ((0xC3 >> pi->k) & 1) {
            ps = func_0015E938(g_sw, 1, pi->v, p);
            if (!ps) continue;
        }
        switch ((unsigned int)pi->k) {
        case 6:
            psPrev = ps;
            break;
        case 0:
            ((void (*)(void *))ps->vt[8].pfn)((char *)ps + ps->vt[8].d);
            break;
        case 1:
            ((void (*)(void *))ps->vt[9].pfn)((char *)ps + ps->vt[9].d);
            break;
        case 2:
            ShowAloGlobs__FP3ALOi(p, pi->v);
            break;
        case 3:
            func_001F69F8(p, pi->v);
            break;
        case 4:
            SetAloSoesByTag__FP3ALOi(p, pi->v);
            break;
        case 5:
            func_001F6B48(p, pi->v);
            break;
        case 7:
            if (FIsBasicDerivedFrom__FP5BASIC3CID(ps, 0x1E)) {
                MSG msg;
                msg.a = 1;
                msg.ps = psPrev ? psPrev : ps;
                ((void (*)(void *, MSG *))ps->vt[51].pfn)((char *)ps + ps->vt[51].d, &msg);
            }
            break;
        case 8:
            if (p->x168 & 2) JoltCm__FP2CMi(g_cm, pi->v);
            break;
        case 9:
            if (p->x168 & 4) TriggerJoyRumbleRumk__FP3JOY4RUMKf(g_joy, pi->v, 0.3f);
            break;
        case 10:
            if (p->x168 & 8) {
                qword q;
                if (psPrev) q = func_001A62E8(psPrev);
                else q = func_001A62E8(p);
                DropPickups__FP6VECTORG9VU_VECTORiiP2LO(D_002DE578, q, pi->v, -100, p);
            }
            break;
        case 11: {
            int *apv[1];
            apv[0] = &pi->v;
            ((void (*)(void *, int, int, int, int **, int))p->vt[3].pfn)((char *)p + p->vt[3].d, 4, 0, 1, apv, 0);
            break;
        }
        case 12:
            ApplyCheckpointTasks__FP2SWiP2LOPv(g_game, 1, pi->v, p);
            break;
        }
    }
}
