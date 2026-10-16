// wip (Claude agent): player message handler (msgs 1,3,4,5,9,11; msg 9 sub-switch 0x15E/161/162/1C7/1C8/27B/27C) then func_1EED78(p+0x26C)+func_1C3E20 base.
// 21/382 diffs: case 0x15E VU scheduling (scalar spill sqc2 0(sp) placed last in target) and a1-vs-v1 for x9BC in case 0x27C.
typedef int qword __attribute__((mode(TI)));
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *D_002DD2FC;     /* g_pdliFirst */
struct VT { struct { short d; short pad; void (*pfn)(); } a[64]; };
#define F(T, p, off) (*(T *)((char *)(p) + (off)))
struct SO { char pad[0x18]; void *p18; };
struct MSG { struct SO *pso; float g; int k; };
struct MSGB { void *p0; void *p4; };
struct ENT { void *po; int x4; };
struct CLOCK { float t; float dt; };
struct GS { char pad[0x4758]; float g4758; };
struct GG { char pad[0x2010]; void *p2010; };
extern struct CLOCK D_002DDED0;
extern struct GS D_003DD490;
extern DL D_003E148C;
extern struct GG *D_002E1E40;
extern float D_002BCC94;
void func_001A15D0(void *p);
void func_002206C8(void *p, int n);
qword func_00204E38(void *p, struct SO *pso, float g);
qword func_001A62E8(void *p);
void func_002205A8(void *p);
int func_00132B10(void *p, int n);
int func_00224590(void *p);
void func_002245B8(void *p);
void func_00130658(void *p);
void func_00141CD0(void *p);
void func_001305B8(void *pa, void *p, float g, int n, float h, void *pb);
void func_0019F170(void *p, int n);
void func_0019F220(void *p, int n);
void *func_001CB250(void *p, int n);
void func_001A58D0(void *p, int a, int b);
void func_00156780(void *p);
void func_001CCC88(void *p, void *q);
void func_00131A00(void *p, float g);
void func_001CD098(void *p, void *q);
void func_00133448(void *p, void *q);
void func_001EED78(void *p, int msg, void *pmsg);
void func_001C3E20(void *p, int msg, void *pmsg);

static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = D_002DD2FC;
    D_002DD2FC = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
static inline qword VecMul(qword v, float g)
{
    qword r;
    union { qword q; float f[4]; } s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
static inline qword VecSub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

void func_00140F90(void *p, int msg, void *pv)
{
    switch (msg) {
    case 3:
        if (pv == F(void *, p, 0x1030) ||
            (F(void *, p, 0x1034) != 0 && pv == F(void *, F(void *, p, 0x1034), 0x30))) {
            F(int, p, 0x1038) = -1;
            if ((unsigned)(F(int, p, 0xDF4) - 8) < 5) {
                func_001A15D0((char *)p + 0xDF0);
            } else {
                switch (F(int, p, 0x11B4)) {
                case 5:
                case 6:
                    func_002206C8((char *)p + 0x11B0, 4);
                    break;
                case 1:
                case 2:
                    func_002206C8((char *)p + 0x11B0, 0);
                    break;
                }
            }
        }
        break;
    case 9: {
        struct MSG *pmsg = (struct MSG *)pv;
        if (pmsg->pso->p18 != p)
            break;
        switch (pmsg->k) {
        case 0x15E: {
            qword v = func_00204E38(p, pmsg->pso, pmsg->g);
            struct VT *pvt;
            qword *pm = &F(qword, p, 0x1B0);
            qword r;
            F(qword, p, 0x190) = VecMul(v, -1.0f);
            pvt = F(struct VT *, p, 0xC);
            __asm__("vmulax.xyz ACC, %1, %2x\n\tvmadday.xyz ACC, %3, %2y\n\tvmaddz.xyz %0, %4, %2z"
                : "=j"(r) : "j"(pm[0]), "j"(v), "j"(pm[1]), "j"(pm[2]));
            ((void (*)(void *, qword))pvt->a[35].pfn)((char *)p + pvt->a[35].d, r);
            break;
        }
        case 0x161:
            F(int, p, 0x1044) = 1;
            break;
        case 0x162: {
            qword v = F(qword, p, 0x1060);
            F(int, p, 0x1044) = 0;
            F(qword, p, 0x1070) = VecSub(v, func_001A62E8(p));
            F(int, p, 0x1078) = 0;
            break;
        }
        case 0x27B:
            if (F(int, p, 0x11B4) != -1)
                func_002205A8((char *)p + 0x11B0);
            break;
        case 0x27C:
            if (F(int, p, 0x4C8) == 0xB) {
                void *po;
                int n;
                if (F(void *, p, 0x4D4) != 0 && func_00132B10(F(void *, p, 0x4D4), 100)) {
                    po = F(void *, p, 0x4D4);
                    if (func_00224590(po))
                        func_002245B8(po);
                }
                n = F(int, p, 0x9BC);
                if (F(void *, p, 0x130C) != 0) {
                    if (n == F(int, p, 0x1314)) {
                        func_00130658((char *)p + 0x1310);
                        F(int, p, 0x1314) = -1;
                    } else {
                        func_00141CD0(p);
                        func_001305B8(F(void *, p, 0x130C), p, 0.0f, 8, 1.0f, (char *)p + 0x1310);
                        F(int, p, 0x1314) = F(int, p, 0x9BC);
                    }
                } else if (n != -1) {
                    func_00141CD0(p);
                    switch (F(int, p, 0x9BC)) {
                    case 0xE:
                        func_0019F170(&D_003DD490, 1);
                        break;
                    case 0x15:
                        func_0019F220(&D_003DD490, 0x15);
                        break;
                    case 0x17: {
                        DLI dli;
                        void *po2;
                        void *pa = func_001CB250(D_002E1E40->p2010, 0);
                        if (pa)
                            func_001A58D0(pa, 0, 3);
                        InitDli(&dli, &D_003E148C);
                        while ((po2 = PvNextDli(&dli)) != 0) {
                            if (F(int, po2, 0x54) == 4 && F(void *, po2, 0x44) == p)
                                func_00156780(po2);
                        }
                        D_002DD2FC = dli.m_pdliNext;
                        D_003DD490.g4758 = D_002DDED0.t + D_002BCC94;
                        break;
                    }
                    }
                }
                F(void *, p, 0x130C) = 0;
                F(int, p, 0x9BC) = -1;
            }
            break;
        case 0x1C8:
            if (F(int, p, 0x4C8) == 0xC)
                func_001CCC88((char *)p + 0x900, F(void *, p, 0x4D4));
            break;
        case 0x1C7:
            if (F(int, p, 0x4C8) == 0xC) {
                func_00131A00(F(void *, p, 0x1030), 1.0f);
                func_001CD098((char *)p + 0x900, F(void *, p, 0x4D4));
            }
            break;
        }
        break;
    }
    case 4: {
        struct MSGB *pm = (struct MSGB *)pv;
        if (pm->p4 == p) {
            int i;
            F(void *, p, 0x108C) = pm->p0;
            for (i = 0; i < F(int, p, 0x1094); i++) {
                void *po = F(struct ENT *, p, 0x1090)[i].po;
                struct VT *pvt = F(struct VT *, po, 0xC);
                ((void (*)(void *))pvt->a[8].pfn)((char *)po + pvt->a[8].d);
                F(struct ENT *, p, 0x1090)[i].x4 = 0;
            }
        }
        break;
    }
    case 5: {
        struct MSGB *pm = (struct MSGB *)pv;
        if (pm->p4 == p && pm->p0 == F(void *, p, 0x108C)) {
            int i;
            F(void *, p, 0x108C) = 0;
            for (i = 0; i < F(int, p, 0x1094); i++) {
                void *po = F(struct ENT *, p, 0x1090)[i].po;
                struct VT *pvt = F(struct VT *, po, 0xC);
                ((void (*)(void *))pvt->a[9].pfn)((char *)po + pvt->a[9].d);
            }
        }
        break;
    }
    case 1:
        if (F(int, p, 0x4C8) == 0xB && F(void *, p, 0x4D4) == pv) {
            func_00133448(pv, p);
            F(void *, p, 0x4D4) = 0;
        }
        break;
    case 11:
        if (((struct MSGB *)pv)->p4 == p) {
            func_00130658((char *)p + 0x1310);
            F(int, p, 0x1314) = -1;
        }
        break;
    }
    func_001EED78((char *)p + 0x26C, msg, pv);
    func_001C3E20(p, msg, pv);
}
