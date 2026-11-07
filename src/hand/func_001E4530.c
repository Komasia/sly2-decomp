struct G { int a; };
extern struct G g_sw;
extern struct G D_003DD040;
extern struct G D_002DE578;
extern float DT_CmJoltMax;
union U { int n; float g; };
struct P { int kind; int x4; int pad[2]; union U u10; union U u14; int x18; };
struct C { char pad[0x18]; int x18; };
struct O { char pad[0x74]; float g74; float g78; char pad2[0x80 - 0x7C]; float a[3]; int pad3; float gMin; float gMax; };
struct O *PloFind__FP3RUNi(struct C *pc, int n);
float GSuck__FPv(struct G *pg);
void *PloFindSwNearest__FP2LO3OIDii(struct G *pg, int k, int a, int b);
void *PsmaFindAloSm__Fi3OID(void *p, int n);
float func_001F11A8(void *p, int n);
float func_001FCFD0(struct G *pg, int n);
static __inline__ float GClamp(float g, float lo, float hi) { if (g < lo) return lo; if (g > hi) return hi; return g; }
// name: SafeHouse port (GCmdDuration)
float GCmdDuration__FP3RUNP7SCPTCMD(struct C *pc, struct P *p)
{
    float g = 0.0f;
    if (p->x4) return g;
    switch (p->kind) {
    case 0xA: {
        struct O *po = PloFind__FP3RUNi(pc, p->u10.n);
        if (po) {
            float t = GSuck__FPv(&D_002DE578);
            float *pa = po->a; float s = pa[0] + t * (pa[1] + t * pa[2]); s = GClamp(s, po->gMin, po->gMax);
            g = po->g74 / (po->g78 * s);
        }
        break;
    }
    case 0xD:
        if (p->x18 != -1) {
            void *px = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, p->u10.n, pc->x18);
            if (px) {
                void *py = PsmaFindAloSm__Fi3OID(px, p->u14.n);
                if (py) g = func_001F11A8(py, p->x18);
            }
        }
        break;
    case 0x32:
        g = DT_CmJoltMax;
        break;
    case 0x23:
    case 0x33:
        g = p->u10.g;
        break;
    case 0x45:
        g = func_001FCFD0(&D_003DD040, p->u10.n);
        break;
    case 0x2C:
    case 0x2D:
    case 0x53:
        g = p->u14.g;
        break;
    }
    return g;
}
