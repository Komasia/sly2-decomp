// wip (Claude agent): SetState(p, st) for a 7-state object (st 0x184, t 0x188): exit-old switch, enter-new switch (E link via func_1CE888, rand spin in st 5).
// ~235/598 diffs, mostly offsets after a few small sched diffs (Dist/vsqrt scheduling, GMax regs, loop nops); frame 0x110 and layout match.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct VT { struct VTE a[64]; };
struct CLOCK { float t; float dt; };
struct GS { char pad[0x4638]; void *p4638; };
struct ST { char pad[0xC]; int xC; char pad1[0x18 - 0x10]; int x18; int c1C; int a20[1]; };
struct SA0 { int x0; int x4; float g8; };
struct E {
    char pad[0x18]; float g18; void *p1C; char pad1[0xA0 - 0x20]; struct SA0 sA0;
    char pad2[0xEC - 0xAC]; struct VT *pvt; char pad3[0x104 - 0xF0]; void *p104;
};
struct O;
struct Q { char pad[0xC]; struct VT *pvt; int x10; char pad1[0x18C - 0x14]; float g18C; struct O *p190; struct O *p194; };
struct R { char pad[0xC]; struct VT *pvt; };
struct OT { char pad[0x11A4]; struct R *pr; struct O *p11A8; };
struct O {
    char pad[0xC]; struct VT *pvt; char pad1[0xE0 - 0x10]; int cE0; char *aE4;
    char pad2[0x158 - 0xE8]; struct ST *pst; struct Q *pq; struct OT *pot; struct R *p164;
    char pad3[0x180 - 0x168]; float g180; int st; float g188; struct E *pe;
};
struct MSG { int k; void *p; };
extern struct CLOCK D_002DDED0;
extern struct GS D_003DD490;
extern char D_002DEB30[];
extern qword D_002A2DD0;
extern qword D_002A4B60;
void func_001CB4B8(void *pv, struct O *p);
void func_001CB488(void *pv, struct O *p);
void func_001F6A68(struct O *p);
void func_001F6978(struct O *p, int n);
void func_001F2AD0(struct O *p, void *pv);
void func_001F6AC8(struct O *p, int n);
void func_001F6B48(struct O *p, int n);
void func_001618F8(struct GS *pgs, float g);
qword func_001A62E8(void *p);
void func_00156C80(struct GS *pgs, int n, qword v, struct Q *pq, void *pv);
void func_001619A0(void *pv, int n, struct O *p);
void func_00161958(struct GS *pgs);
void func_001F5720(struct O *p, int n);
void func_001F57C0(struct O *p, int n);
void func_001F5880(struct O *p, qword v);
void func_001A58D0(struct O *p, void *pv, int n);
void func_001A6BE8(struct O *p, void *pv);
void func_001F7C68(struct O *p, float g);
struct E *func_001CE888(struct GS *pgs, int n, int m);
void func_001CF578(struct E *pe, struct O *p);
void func_001CFD30(struct E *pe);
float func_0011D448(float a, float b);
void func_0013C560(struct O *p, int st);

#define VCALL(po, slot, T) ((T)(po)->pvt->a[slot].pfn)((char *)(po) + (po)->pvt->a[slot].d
typedef void (*PFN3)(void *, int, int, int, int, int);
typedef void (*PFNV)(void *);
typedef void (*PFNQ)(void *, qword);
typedef void *(*PFNP)(void *);
typedef void (*PFNM)(void *, struct MSG *);
typedef void (*PFNE)(void *, qword, int, float);

static inline float Dist(qword a, qword b)
{
    qword d;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x $vf2, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, $vf2, %0z"
        : "+j"(d) : : "vf2");
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %1, $vf0, Q\n\tqmfc2.ni %0, %1" : "=r"(g), "+j"(d));
    return g;
}

static inline float GMax(float a, float b) { return a < b ? b : a; }

#define LINKE(pe, PA, PB) do { \
    struct VTE *pvte = &(pe)->pvt->a[1]; \
    float g; \
    ((PFNE)pvte->pfn)((char *)(pe) + pvte->d, func_001A62E8(PA), 0, 1.0f); \
    func_001CF578(p->pe, p); \
    g = Dist(func_001A62E8(PA), func_001A62E8(PB)); \
    p->pe->p1C = (PB); \
    p->pe->g18 = GMax(250.0f, g) * 0.002f; \
    { struct SA0 *ps = &p->pe->sA0; ps->x0 = 0; ps->g8 = -3000.0f; ps->x4 = 0; } \
    p->pe->p104 = (PA); \
    func_001CFD30(p->pe); \
    VCALL(p, 8, PFNV)); \
} while (0)

static inline void Notify(struct R *pr, int k)
{
    struct MSG msg;
    msg.p = pr;
    msg.k = k;
    VCALL(pr, 51, PFNM), &msg);
}

void func_0013C560(struct O *p, int st)
{
    int stOld;
    struct OT *pot;
    struct OT *pot4;
    int i;

    if (p->st == st)
        return;
    if (D_003DD490.p4638 != 0) {
        int fOld = p->st >= 2;
        int fNew = st >= 2;
        if (fOld) {
            if (!fNew)
                func_001CB4B8(D_003DD490.p4638, p);
        } else if (fNew) {
            func_001CB488(D_003DD490.p4638, p);
        }
    }
    stOld = p->st;
    pot = p->pot;
    pot4 = pot;
    switch (stOld) {
    case -1:
        break;
    case 0:
        func_001F6A68(p);
        for (i = 0; i < p->pst->c1C; i++)
            func_001F6978(p, p->pst->a20[i]);
        for (i = 0; i < p->cE0; i++)
            func_001F2AD0(p, p->aE4 + i * 0xB0);
        if (p->pst->x18 != -1)
            func_001F6AC8(p, p->pst->x18);
        break;
    case 1:
        if (p->pst->xC)
            func_001618F8(&D_003DD490, p->pq->g18C + 0.99f);
        func_00156C80(&D_003DD490, 1, func_001A62E8(p->pq), p->pq, (char *)p->pq + 0x198);
        if (st == 2)
            func_001619A0(D_002DEB30, 0x2F, p);
        p->pq->p194 = 0;
        p->pq = 0;
        VCALL(p, 3, PFN3), 5, 0, 0, 0, 0);
        break;
    case 2:
        p->pe = 0;
        if (st == 4)
            p->g180 = 0.3f;
        break;
    case 3:
        p->pe = 0;
        break;
    case 4:
        p->pot = 0;
        VCALL(pot4->pr, 9, PFNV));
        pot4->p11A8 = 0;
        if (p->pst->x18 != -1)
            func_001F6AC8(p, p->pst->x18);
        if (p->pst->xC)
            func_00161958(&D_003DD490);
        break;
    case 5: {
        struct R *pr = p->p164;
        if (pr)
            Notify(pr, 1);
        func_001F5720(p, 1);
        func_001F57C0(p, 1);
        VCALL(p, 35, PFNQ), D_002A2DD0);
        VCALL(p, 36, PFNQ), D_002A2DD0);
        func_001F5880(p, D_002A2DD0);
        break;
    }
    case 6:
        p->g180 = 0.0f;
        break;
    }

    p->st = st;
    p->g188 = D_002DDED0.t;

    switch (st) {
    case 0:
        p->pst = 0;
        func_001A58D0(p, 0, 0);
        VCALL(p, 9, PFNV));
        break;
    case 1:
        func_00156C80(&D_003DD490, -1, D_002A2DD0, 0, (char *)p->pq + 0x198);
        func_001A6BE8(p, VCALL(p->pq, 31, PFNP)));
        func_001A58D0(p, (void *)p->pq->x10, 3);
        p->pq->p194 = p;
        if (stOld != 3) {
            VCALL(p, 9, PFNV));
            func_001F7C68(p, 0.5f);
        }
        VCALL(p, 3, PFN3), 6, 0, 0, 0, 0);
        break;
    case 2:
    case 6:
        VCALL(p->pot->pr, 8, PFNV));
        if (p->st == 2) {
            p->pe = func_001CE888(&D_003DD490, 6, 0);
        } else {
            p->pe = 0;
            VCALL(p, 3, PFN3), 6, 0, 0, 0, 0);
            VCALL(p, 3, PFN3), 5, 0, 0, 0, 0);
        }
        {
            struct E *pe = p->pe;
            if (pe)
                LINKE(pe, p, p->pot->pr);
        }
        func_001A6BE8(p, VCALL(p->pot->pr, 31, PFNP)));
        func_001A58D0(p, p->pot->pr, 3);
        if (!p->pe)
            func_0013C560(p, 4);
        break;
    case 3: {
        struct E *pe;
        func_001A6BE8(p, VCALL(p->pq, 31, PFNP)));
        func_001A58D0(p, (void *)p->pq->x10, 3);
        pe = func_001CE888(&D_003DD490, 6, 0);
        p->pe = pe;
        if (pe)
            LINKE(pe, pot->pr, p);
        if (!p->pe)
            func_0013C560(p, 1);
        break;
    }
    case 4:
        p->pot->p11A8 = p;
        if (p->pst->x18 != -1)
            func_001F6B48(p, p->pst->x18);
        break;
    case 5: {
        union { qword q; float f[4]; } v;
        union { qword q; float f[4]; } u;
        union { qword q; float f[4]; } s;
        union { qword q; float f[4]; } w;
        float a, b, c;
        float lo = -6.2831855f, hi = 6.2831855f;
        (void)&w;
        func_001A58D0(p, 0, 3);
        func_001F5720(p, 0);
        func_001F57C0(p, 0);
        {
            qword *pv = (qword *)VCALL(p, 31, PFNP));
            __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(1000.0f));
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(v.q) : "j"(*pv), "j"(s.q));
            VCALL(p, 35, PFNQ), v.q);
        }
        a = func_0011D448(lo, hi);
        b = func_0011D448(lo, hi);
        c = func_0011D448(lo, hi);
        u.f[0] = a;
        u.f[1] = b;
        u.f[2] = c;
        VCALL(p, 36, PFNQ), u.q);
        func_001F5880(p, D_002A4B60);
        func_001619A0(D_002DEB30, 0x30, p);
        break;
    }
    }
}
