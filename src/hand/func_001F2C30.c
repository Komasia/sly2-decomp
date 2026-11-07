typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[12]; };
struct S8 { int a, b; };
struct E { char pad[0xDC]; void *pDC; };
struct L { char pad[0xC]; struct VT *pvt; char pad1[0x24 - 0x10]; struct L *next; char pad1b[0x40 - 0x28]; int v40; char pad2[0x64 - 0x44]; struct L *first; char pad3[0x70 - 0x68]; struct L *end; char pad4[0xE8 - 0x74]; struct E *pe; };
struct H { char pad[0x2C]; int n2C; };
struct G { char pad[0x45CC]; struct H *ph; };
extern struct G g_sw;
extern struct S8 D_002A8270;
void OnLoAdd__FP2LO(struct L *);
void UpdateAloXfWorlds__FP3ALO(struct L *);
void AddAloSoes__FP3ALO(struct L *);
qword PosOfLo__FP2LO(struct L *);
void *PregionAt__FG9VU_VECTORi(qword, int);
void SetAloRegion__FP3ALOP9NAVREGION(struct L *, void *);
void PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(struct G *, struct L *, struct S8, int);
void OnSoAdd__FP2SO(struct L *p)
{
    struct L *q;
    void *pv;
    int unused[4];
    int v;
    OnLoAdd__FP2LO(p);
    UpdateAloXfWorlds__FP3ALO(p);
    AddAloSoes__FP3ALO(p);
    v = p->v40;
    if ((v ^ 1) & 1) *(int *)v |= 0x14;
    else p->v40 = v | 0x14;
    pv = p->pe ? p->pe->pDC : 0;
    if (pv) {
        if (g_sw.ph && g_sw.ph->n2C)
            SetAloRegion__FP3ALOP9NAVREGION(p, PregionAt__FG9VU_VECTORi(PosOfLo__FP2LO(p), 1));
        else
            PostDeferredPointerCall__FPvUi22PFNDEFERREDPOINTERCALLi(&g_sw, p, D_002A8270, 0);
    }
    for (q = p->first; q != p->end; q = q->next)
        q->pvt->a[11].pfn((char *)q + q->pvt->a[11].d);
}
