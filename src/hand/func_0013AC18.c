/* SweepProjectile: the projectile's previous sweep hits are released (UpdateSwPox 2), then every sweepable solid
 * entry (+0xF0, flags 0x100) in the world list D_003E13B4 whose root object has the flag bit (LO +0x2C) is tested:
 * the segment from the entry's position to the point +0x50 of the projectile's +0xE4 against the sphere of the
 * root's attachment radius around the projectile; a hit (4 at most) records the
 * object, the point and the normal, and the pair is made overlapping. Layout: SafeHouse port (projectile.cpp). */
typedef int qword __attribute__((mode(TI)));
struct OXA { char pad[0x30]; float sRadius; };   /* field: SafeHouse port (so.h OXA) */
struct LO { char pad[0x28]; int x28; signed char x2C; char x2D; long k:4; long :8; unsigned int f:1; char pad2[0xEC - 0x30]; struct OXA *poxa; };
struct N { char pad[0x60]; struct LO *plo; };
struct SO { char pad[0x10]; struct SO *pparent; char pad1[0xE0 - 0x14]; struct SO *pnext; int xE4; int grfE8; struct N *pn; int xF0; };
struct SWEEP { qword pos; qword normal; int n20; struct LO *plo; int pad[2]; };   /* a sweep hit (SafeHouse SWEEP) */
struct SOE { char pad[0x50]; qword pos50; };
struct BOMB { char pad[0xE4]; struct SOE *psoe; int xE8; struct OXA *poxa; char pad1[0x1F8 - 0xF0]; int csweep; struct SWEEP *asweep; };   /* field: SafeHouse port (projectile.cpp) */
struct HIT { qword pos; qword a; qword normal; qword b; qword c; qword d; };
struct SW { char pad[0x3F24]; struct SO *psoFirst; };
extern struct SW g_sw;
extern struct { struct SO *pbomb; } D_003E13B4;
void UpdateSwPox__FP2SWP3OXAT1Uc(struct SW *psw, struct OXA *pa, struct OXA *pb, int n);
qword PosOfLo__FP2LO(void *pbomb);
int ClipSegmentSphere__FG9VU_VECTORfN20iP3LSG(qword a, qword b, qword c, int n, struct HIT *phit, float g);
// name: SafeHouse port (SweepProjectile)
void SweepProjectile__FP3ALO(struct BOMB *pbomb)
{
    int i;
    struct SO *pso;
    int unused[4];
    struct HIT hit;
    for (i = 0; i < pbomb->csweep; i++)
        UpdateSwPox__FP2SWP3OXAT1Uc(&g_sw, pbomb->poxa, pbomb->asweep[i].plo->poxa, 2);
    pbomb->csweep = 0;
    for (pso = D_003E13B4.pbomb; pso; pso = pso->pnext) {
        struct LO *plo;
        struct SO *pp;
        if (!pso->xF0)
            continue;
        if (!(pso->grfE8 & 0x100))
            continue;
        plo = 0;
        for (pp = pso->pparent; pp; pp = pp->pparent) {
            if (pp->pn) {
                plo = pp->pn->plo;
                break;
            }
        }
        if (!plo)
            continue;
        if (!plo->f)
            continue;
        {
            qword a = PosOfLo__FP2LO(pso);
            struct OXA *poxa = plo->poxa;
            qword b = pbomb->psoe->pos50;
            if (ClipSegmentSphere__FG9VU_VECTORfN20iP3LSG(a, b, PosOfLo__FP2LO(pbomb), 1, &hit, poxa->sRadius)) {
                struct SWEEP *pe;
                qword d, t;
                register qword vp __asm__("vf2");
                register qword vn __asm__("vf1");
                register int n __asm__("$2");
                UpdateSwPox__FP2SWP3OXAT1Uc(&g_sw, pbomb->poxa, plo->poxa, 1);
                pe = &pbomb->asweep[pbomb->csweep++];
                pe->plo = plo;
                __asm__("" : "+r"(pe));
                vp = hit.pos;
                pe->pos = vp;
                vn = hit.normal;
                __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(t) : "j"(vp), "j"(vn));
                __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(d));
                pe->normal = vn;
                pe->n20 = n;
                if (pbomb->csweep >= 4)
                    break;
            }
        }
    }
}
