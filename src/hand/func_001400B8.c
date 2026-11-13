typedef int qword __attribute__((mode(TI)));
struct K { int a; int b; };
extern struct K D_002A4D10;
struct G { char pad[0x3BF4]; int grf; char pad2[0x3D58 - 0x3BF8]; int cid; };
extern struct G g_sw;
struct VTE { short d; short pad; void *pfn; };
struct M3 { qword r[3]; };
struct AREQ { int cb; int cbAlign; };
struct SO { float m[0x40 / 4]; char pad[0x94 - 0x40]; int x94; char pad2[0xA4 - 0x98]; int id; };
struct O { void *pad[3]; struct VTE *vt; };
struct P {
    int pad[3]; struct VTE *vt; char pad1[0x54 - 0x10]; struct SO *pso;
    char pad2[0x1088 - 0x58]; int x1088; char pad3[4]; struct O **apo; int cpo;
};
extern char D_002BC9F0[];
void PostStepLoad__FP4STEP(struct P *);
void BindLoParts__FP3ALOiPv(struct P *, int, void *);
void PostLoadJump__FP4JUMP(void *);
void PostLoadInteract__FP5ACTOR(void *);
void func_0019F3F0(void *);
void func_001A1098(void *);
void PostLoadBinoc__FP5ACTOR(void *);
void PostLoadJtThrow__FP7JTTHROW(void *);
void BindSlopeBlend__FP10SLOPEBLEND(void *);
int CploFindSwNearest__FP2LO3OIDiiii(struct G *, int, int, struct P *, int, void **);
void *PvAllocSwClearImpl__Fi(struct AREQ *);
void func_00141EF8(struct P *);
void StartPlayerCounters__FP5ACTORi(struct P *, int);
int PtargetrecOf__FP2LO(struct P *);
void SetSoMass__FP2SOf(struct P *, float);
qword PosOfLo__FP2LO(struct P *);
struct M3 *MatJtLo__FP2LO(struct P *);
void *s1_memset(void *, int, int);
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(struct G *, struct P *, struct K, int);

// name: SafeHouse port (PostLoadActorParts)
void PostLoadActorParts__FP5ACTOR(struct P *p)
{
    void *apv[16];
    int c;
    int i;

    PostStepLoad__FP4STEP(p);
    BindLoParts__FP3ALOiPv(p, 0x35, D_002BC9F0);
    PostLoadJump__FP4JUMP((char *)p + 0x2C0);
    PostLoadInteract__FP5ACTOR((char *)p + 0x4C0);
    func_0019F3F0((char *)p + 0x9E0);
    func_001A1098((char *)p + 0xDF0);
    PostLoadBinoc__FP5ACTOR((char *)p + 0xF00);
    PostLoadJtThrow__FP7JTTHROW((char *)p + 0x11B0);
    BindSlopeBlend__FP10SLOPEBLEND((char *)p + 0xF50);
    c = CploFindSwNearest__FP2LO3OIDiiii(&g_sw, 0x401, 0x2AB, p, 0x10, apv);
    if (c) {
        struct AREQ req;
        struct AREQ *preq = &req;
        preq->cb = c * 8;
        p->cpo = c;
        preq->cbAlign = 0x10;
        p->apo = PvAllocSwClearImpl__Fi(preq);
        for (i = 0; i < c; i++) {
            struct O *po;
            struct VTE *e;
            p->apo[i * 2] = apv[i];
            po = p->apo[i * 2];
            e = &po->vt[9];
            ((void (*)(void *))e->pfn)((char *)po + e->d);
        }
    }
    {
        struct VTE *e = &p->vt[79];
        ((void (*)(void *, int))e->pfn)((char *)p + e->d, 0);
    }
    {
        struct VTE *e = &p->vt[104];
        ((void (*)(void *))e->pfn)((char *)p + e->d);
    }
    func_00141EF8(p);
    StartPlayerCounters__FP5ACTORi(p, g_sw.grf & 4);
    p->x1088 = PtargetrecOf__FP2LO(p);
    SetSoMass__FP2SOf(p, 0.25f);
    if (p->pso->x94 == 0) {
        qword q = PosOfLo__FP2LO(p);
        struct M3 m = *MatJtLo__FP2LO(p);
        struct SO *pso = p->pso;
        s1_memset(pso, 0, 0x40);
        pso->m[0] = pso->m[5] = pso->m[10] = pso->m[15] = 1.0f;
        g_sw.cid++;
        p->pso->id = g_sw.cid;
        {
            struct VTE *e = &p->vt[18];
            ((void (*)(void *))e->pfn)((char *)p + e->d);
        }
        {
            struct VTE *e = &p->vt[29];
            ((void (*)(void *, qword))e->pfn)((char *)p + e->d, q);
        }
        {
            struct VTE *e = &p->vt[30];
            ((void (*)(void *, struct M3 *))e->pfn)((char *)p + e->d, &m);
        }
    }
    PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(&g_sw, p, D_002A4D10, 0);
}
