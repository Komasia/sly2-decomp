struct VTE { short d; short pad; void (*pfn)(); };
struct EV { float g0; unsigned int k; void *pv; union { float g; int n; } uC; };
struct Q { char pad[0xA0]; int cev; struct EV *aev; };
struct A0 { int x0; int x4; int x8; int xC; float g10; float g14; float g18; };
struct A17 { int x0; int x4; int x8; float gC; };
struct A20 { int x0; int x4; float g8; };
struct B { int pad[3]; virtual void Begin(); virtual void End(); virtual void F3(int, int, int, void **, int); virtual void F4(int, struct MSG *); };
struct MSG;
struct P : B { int x10; struct Q *pq; void *po; float g1C; char pad2[0x40 - 0x20]; float g40;
    char pad3[0x5C - 0x44]; char a5C[4]; };
struct G { P *p; G(P *pp) : p(pp) { p->Begin(); } ~G() { p->End(); } };
struct MSG { struct P *p; float g; void *pv; };
extern char g_sw[];
extern "C" {
extern char g_cm[];
extern char g_joy[];
void *func_00131270(struct P *);
void PlayAsegaSound(void *, int, int, int, int, void *, void *, struct Q *, void *, float, float, float) asm("PlayAsegaSound__FfffPviiiiN33PPv");
void StopAsegaSound(void *, void *, struct Q *, void *) asm("StopAsegaSound__FP5ASEGAiPvT2");
void JoltCm(void *, void *) asm("JoltCm__FP2CMi");
void TriggerJoyRumbleRumk(void *, void *, float) asm("TriggerJoyRumbleRumk__FP3JOY4RUMKf");
void *func_0015E938(void *, int, void *, void *);
int func_00132EA0(void *);
void ApplyAseg(void *, int, int, int, float, float) asm("ApplyAseg__FP4ASEGiiffPP5ASEGA");
void StartScptImpl(void *, int) asm("StartScptImpl__FP2LOi");
void SetAsegaTime(struct P *, int, float, float) asm("SetAsegaTime__FP5ASEGAiff");
void RetractAsega(struct P *) asm("RetractAsega__FP5ASEGA");
void SetAsegaEventSound(struct P *, int) asm("SetAsegaEventSound__FP5ASEGAi");
void AddRemoveByOid(void *, int, void *, void *, struct Q *, float) asm("AddRemoveByOid__FPv3OIDif");
void func_00210538(void *, int, int, int, void *, struct Q *, float);
void func_00210408(void *, int, void *, int, void *, void *, struct Q *);
void func_002104A0(void *, int, void *, int, void *, void *, struct Q *);
void StartHudTimer(void *, float) asm("StartHudTimer__FPvf");
void StopHudTimer(void *) asm("StopHudTimer__FPv");
void SetEyesClosedOf(void *, int, int, void *, struct Q *, float) asm("SetEyesClosedOf__FP2LOiif");
void SnapAsegaXfs(struct P *, void *) asm("SnapAsegaXfs__FP5ASEGAi");
void func_001F81E0(void *, int);
int FIsBasicDerivedFrom(void *, int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
void func_00143090(void *, void *, void *, void *);
}
// name: SafeHouse port (FireAsegaEvent)
extern "C" void FireAsegaEvent__FP5ASEGAP6ASEGEV(struct P *p, struct EV *pev)
{
    G g(p);
    struct MSG msg;
    void *pv;
    struct Q *pq;
    int f;
    p->g1C = pev->g0;
    pq = p->pq;
    f = 0;
    if (p->g40 < 0.0f && pev >= pq->aev)
        f = pev < pq->aev + pq->cev;
    switch (pev->k) {
    case 0: {
        void *v = func_00131270(p);
        struct A0 *pa = (struct A0 *)pev->pv;
        PlayAsegaSound(g_sw, pa->x0, pa->x4, pa->x8, pa->xC, p->po, v, pq, p->a5C, pa->g10, pa->g14, pa->g18);
        break;
    }
    case 1:
        StopAsegaSound(g_sw, pev->pv, pq, p->a5C);
        break;
    case 2:
        JoltCm(g_cm, pev->pv);
        break;
    case 3:
        TriggerJoyRumbleRumk(g_joy, pev->pv, pev->uC.g);
        break;
    case 4: {
        void *po = func_0015E938(g_sw, 4, pev->pv, func_00131270(p));
        if (po) {
            switch (func_00132EA0(po)) {
            case 0x6D:
                ApplyAseg(po, 0, 0, 0, 0.0f, 1.0f);
                break;
            case 0x72:
                StartScptImpl(po, 0);
                break;
            }
        }
        break;
    }
    case 5:
        SetAsegaTime(p, 0, *(float *)&pev->pv, pev->uC.g);
        break;
    case 6:
        RetractAsega(p);
        break;
    case 9:
    case 10:
        {
            int fT = (pev->k == 9);
            fT ^= f;
            SetAsegaEventSound(p, fT);
        }
        break;
    case 7:
    case 8: {
        int fT = (pev->k == 7);
        fT ^= f;
        AddRemoveByOid(g_sw, fT, pev->pv, func_00131270(p), pq, pev->uC.g);
        break;
    }
    case 11: {
        msg.p = p;
        msg.g = pev->g0;
        msg.pv = pev->pv;
        p->F4(9, &msg);
        break;
    }
    case 12: {
        { void **ppv = &pv; *ppv = &pev->pv; p->F3(4, 0, 1, ppv, 0); }
        break;
    }
    case 17: {
        struct A17 *pa = (struct A17 *)pev->pv;
        func_00210538(g_sw, pa->x0, pa->x4, pa->x8, func_00131270(p), pq, pa->gC);
        break;
    }
    case 13:
    case 14: {
        int fT = (pev->k == 13);
        fT ^= f;
        func_00210408(g_sw, fT, pev->pv, pev->uC.n, p->po, func_00131270(p), pq);
        break;
    }
    case 15:
    case 16: {
        int fT = (pev->k == 15);
        fT ^= f;
        func_002104A0(g_sw, fT, pev->pv, pev->uC.n, p->po, func_00131270(p), pq);
        break;
    }
    case 18:
        StartHudTimer(g_sw, p->g1C);
        break;
    case 19:
        StopHudTimer(g_sw);
        break;
    case 20: {
        struct A20 *pa = (struct A20 *)pev->pv;
        SetEyesClosedOf(g_sw, pa->x0, pa->x4, func_00131270(p), pq, pa->g8);
        break;
    }
    case 21:
        SnapAsegaXfs(p, pev->pv);
        break;
    case 22:
        func_001F81E0(p->po, (int)pev->pv);
        break;
    case 23:
        func_001F81E0(p->po, -1);
        break;
    case 24:
        if (p->po && FIsBasicDerivedFrom(p->po, 0x34)) {
            char *pb = (char *)pev->pv;
            func_00143090(p->po, pb, pb + 8, pb + 0x10);
        }
        break;
    }
}
