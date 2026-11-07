typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; int (*pfn)(); };
struct J { char pad[0xC]; struct VTE *vt; char pad1[0x2DC - 0x10]; int x2DC; };
struct P { char pad[0xC]; struct VTE *vt; char pad1[0x150 - 0x10]; int x150; int x154; float g158; float g15C; int x160; int x164; };
struct G { char pad[0x3B0C]; int x3B0C; };
extern struct G g_sw;
void UpdateSo__FP2SOf(struct P *p);
struct J *PloPlayerPo__FP2SW(struct G *pg);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct J *pj, int k);
qword PosOfLo__FP2LO(void *p);
static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
// name: SafeHouse port (UpdateMarker)
void UpdateMarker__FP2LO(struct P *p)
{
    struct J *pj;
    int f;
    float r;
    UpdateSo__FP2SOf(p);
    pj = PloPlayerPo__FP2SW(&g_sw);
    if (pj && FIsBasicDerivedFrom__FP5BASIC3CID(pj, p->x154)) {
        r = p->x164 ? p->g15C : p->g158;
        f = GDist(PosOfLo__FP2LO(pj), PosOfLo__FP2LO(p)) < r;
    } else f = 0;
    if ((p->x150 == 0 || p->x150 == 2) && g_sw.x3B0C)
        f = 0;
    if (f && FIsBasicDerivedFrom__FP5BASIC3CID(pj, 0x34) &&
        (pj->x2DC != -1 || ((int (*)(void *))pj->vt[77].pfn)((char *)pj + pj->vt[77].d) == 2))
        f = p->x164;
    if (f != p->x164) {
        p->x164 = f;
        if (f)
            ((void (*)(void *, int, int, int, int, int))p->vt[3].pfn)((char *)p + p->vt[3].d, 5, 0, 0, 0, 0);
        else
            ((void (*)(void *, int, int, int, int, int))p->vt[3].pfn)((char *)p + p->vt[3].d, 6, 0, 0, 0, 0);
    }
}
