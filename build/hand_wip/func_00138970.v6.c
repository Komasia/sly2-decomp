/* v6 (Claude agent, laneC27 2026-10-23): 13 -> 12. The iSeg copy asm replaced by `int sh = iSeg * 8;` plus an empty volatile "+r"(sh) asm (sh used as a byte offset). loop.c still hoists the shift (sll s4 before the loop, daddu copy in the branch), but the count drops. A goto-built loop (no loop notes: no hoisting at all, no asms needed, target else-branch exact) is 28: p/i get s1/s2 swapped since refs are no longer loop-weighted. */
/* v5 (Claude agent, laneC26 2026-10-23): aligned 28 -> 13. (1) 0.0f from a commented volatile `mtc1 $0` asm inside the loop (loop.c no longer hoists it: frame 0xF0, the !po stores use the compare register f1), placed between the i*xC0 mult and the base add (split pe computation) like the target. (2) !po stores written f[2], f[1], f[0] (gcc rotates: target order f0, f2, f1). (3) iSeg copied through an empty volatile "+r" asm in the else branch so iSeg*8 is not hoisted (costs a daddu copy). (4) Madd split: ToVf qmtc2 + fused vadda/vmaddx taking a qword s; s1 = ToVf; a = Madd; s2 = ToVf; w.q = s1; b = Madd; w.q = s2 (target stores the first s after the 2nd qmtc2; s1 vf5). (5) ONE pin: the 2nd pe->w reload in $16 (pe dying). Left: the daddu v1,s4 copy in the else branch (target sll v1,s4,3 directly; "+r"(iSeg) itself: 20, s3/s4 swap) and the 2nd Madd VF numbers (target v30 vf1 / s2 vf4; ours v30 vf4 / s2 vf1; alloc-only "j"(v), swapped operands, v30 copied via "+j": no gain). */
/* wip (Claude agent, 2026-10-17): aligned 28 (was 52). for-loop gives target s-reg numbering and a0 reuse at loop head; E.w read as int (lw->qmtc2); vadda operand order fixed. Left: loop.c hoists 0.0f (f22, frame 0x100) and iSeg*8 (s4) out of the loop; target keeps them inside. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
extern qword D_002A2DD0;
struct VTE { short d; short pad; void *pfn; };
struct O { struct VTE *vt; };
struct SEG { float g0; float g4; };
struct CL { char pad[0x74]; float x74; };
struct E { union { float w; int iw; } u; struct CL *p4; };
struct A { char pad[0x74]; float x74; char pad2[0xC0 - 0x78]; int xC0; int xC4; char *xC8; };
struct B { int x0; void *x4; struct SEG *x8; };
struct P { int pad; struct A *p4; struct B *x8; struct O **xC; qword x10; };
int func_00138370(void *, struct SEG *, float *, float, float);
static __inline__ qword ToVf(int g)
{
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    return s;
}
static __inline__ qword Madd(qword a, qword v, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(s));
    return r;
}

void func_00138970(struct P *p, qword *ppos, qword *prot, float t, float rate)
{
    float u;
    int iSeg;
    struct SEG *pseg;
    VU a, b;
    VU v20, v30, w;
    int i;
    if (p->x8 == 0) {
        u = t / p->p4->x74;
    } else {
        float tLocal;
        iSeg = func_00138370(p->x8->x4, p->x8->x8, &tLocal, t, p->p4->x74);
        pseg = &p->x8->x8[iSeg];
        u = tLocal / pseg->g4;
    }
    b.q = a.q = D_002A2DD0;
    for (i = 0; i < p->p4->xC4; i++) {
        int off = i * p->p4->xC0;
        char *base = p->p4->xC8;
        struct E *pe;
        struct O *po;
        float zero;
        __asm__ __volatile__("mtc1 $0, %0" : "=f"(zero)); /* volatile asm (Claude agent): keeps the 0.0f inside the loop like the target */
        pe = (struct E *)(base + off);
        if (pe->u.w == zero)
            continue;
        po = p->xC[i];
        if (!po) {
            a.q = p->x10;
            b.f[2] = zero;
            b.f[1] = zero;
            b.f[0] = zero;
        } else {
            float g0, g1;
            if (!p->x8) {
                g1 = rate * pe->p4->x74 / p->p4->x74;
                g0 = u * pe->p4->x74;
            } else {
                int sh = iSeg * 8;
                struct SEG *ps;
                float gMax;
                __asm__ __volatile__ ("" : "+r"(sh));
                ps = (struct SEG *)((char *)pe + p->x8->x0 + sh);
                gMax = pe->p4->x74;
                g0 = ps->g0 + u * ps->g4;
                g1 = rate * ps->g4 / pseg->g4;
                if (gMax < g0)
                    g0 -= gMax;
            }
            {
                struct VTE *e = &po->vt[3];
                ((void (*)(void *, float, float, VU *, VU *))e->pfn)((char *)po + e->d, g0, g1, &v20, &v30);
            }
        }
        {
            qword s1, s2;
            s1 = ToVf(pe->u.iw);
            a.q = Madd(a.q, v20.q, s1);
            { register int wb asm("$16") = pe->u.iw; /* register pin (Claude agent): target reloads pe->w into pe's dying register s0 */ __asm__("qmtc2.ni %1, %0" : "=j"(s2) : "r"(wb)); }
            w.q = s1;
            b.q = Madd(b.q, v30.q, s2);
            w.q = s2;
        }
    
    }
    if (ppos)
        *ppos = a.q;
    if (prot)
        *prot = b.q;
}
