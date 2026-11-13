typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *s_pdliFirst;
struct CLOCK { float t; float dt; char pad[8]; float g10; };
extern struct CLOCK g_clock;
extern char D_002E65E0[];
extern char D_003DD040[];
extern char g_cm[];
extern char D_002DD598[];
struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
struct E { int grf; struct O *po; };
struct L { char pad[0x84]; struct L *pnext; };
struct S { char pad[0x3D88]; DL dl; char pad1[0x3EAC - 0x3D94]; struct L *pl; char pad2[0x3F14 - 0x3EB0]; int c; int x3F18; int *pi; struct E *ae;
    char pad3[0x3FFC - 0x3F24]; DL dl2; };
void RunDeferredSpliceEvents__FP2SW(struct S *p);
void UpdateSwActivation(struct S *p) asm("UpdateSwActivation__FP2SW");
void func_002267C0(struct S *p);
void UpdatePadctl__FP6PADCTL(struct L *pl);
void AgeSwContacts__FPv(struct S *p);
void UpdateGuardsFrozen__FP2SW(struct S *p);
void UpdateAsega__FP5ASEGA(void *pv);
void ExpireNoises__FPv(void *pv);
void UpdateSwPhys__FP2SW(struct S *p);
void UpdateNavPolys__Fv(void);
void func_001EC968(void);
void UpdateSave__FP4SAVE(void *pv);
void UpdateSoundMgr__FPv(void *pv);
void UpdateCm__FP2CM(void *pv);
void StackCounters__FP2SW(struct S *p);
void func_00128148(void *pv);
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = s_pdliFirst;
    s_pdliFirst = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
// name: SafeHouse port (RegisterSwPass)
void RegisterSwPass__FPv(struct S *p)
{
    RunDeferredSpliceEvents__FP2SW(p);
    UpdateSwActivation(p);
    if (g_clock.dt <= 0.0f) {
        func_002267C0(p);
    } else {
        struct L *pl;
        int i;
        DLI dli, dli2;
        void *pv;
        for (pl = p->pl; pl; pl = pl->pnext)
            UpdatePadctl__FP6PADCTL(pl);
        AgeSwContacts__FPv(p);
        p->pi = &i;
        for (i = 0; i < p->c; i++) {
            struct E *pe = &p->ae[i];
            if (pe->grf & 2) {
                struct O *po = pe->po;
                ((void (*)(void *))po->vt[16].pfn)((char *)po + po->vt[16].d);
            }
        }
        p->pi = 0;
        UpdateGuardsFrozen__FP2SW(p);
        InitDli(&dli, &p->dl);
        while ((pv = PvNextDli(&dli)) != 0)
            UpdateAsega__FP5ASEGA(pv);
        InitDli(&dli2, &p->dl2);
        while ((pv = PvNextDli(&dli2)) != 0)
            ExpireNoises__FPv(pv);
        RunDeferredSpliceEvents__FP2SW(p);
        UpdateSwPhys__FP2SW(p);
        UpdateNavPolys__Fv();
        func_001EC968();
        RunDeferredSpliceEvents__FP2SW(p);
        s_pdliFirst = dli.m_pdliNext;
    }
    UpdateSave__FP4SAVE(D_002E65E0);
    UpdateSoundMgr__FPv(D_003DD040);
    if (0.0f < g_clock.g10)
        UpdateCm__FP2CM(g_cm);
    StackCounters__FP2SW(p);
    func_00128148(D_002DD598);
}
