// v12 (Claude agent, laneC30 2026-10-24): aligned 11 -> 8. Else branch now matches: vF0 read into a qword v kept in a pseudo by a commented empty "+j" asm, an earlyclobber SubE with an allocation-only 2nd "j"(pos), and VU_FLOAT vf(p->g100) as a named local before the call. Left: the gather-loop g100 lw/por order (target lw after lqc2 0x20, por after lqc2 0x30) and the pos vf3/vf4 numbering there.
// v11 (Claude agent, laneC28 2026-10-24): aligned 13 -> 11. Gather loop: the VU_FLOAT is a named local built before d and passed to a RotK whose asm takes it as an allocation-only "r" input, so the g100 lw is scheduled before the Rot. Left: the lw now issues before the lui of &D_002DDF40, so that high gets v1 (target v0, lw after the addiu s0 through the anti-dep); the same dependence on the Add (AddK) is too weak (15), on the Sub 13. Else branch unchanged.
// v10 (Claude agent, laneC24 2026-10-23): aligned 17 -> 13. Gather loop: the VU_FLOAT is built with a NON-volatile 1-arg form (no d dependence), and d's extra refs come from a commented empty `__asm__("" : "+j"(d))` right after the Sub instead of alloc-only operands on the ctor. d stays caller-saved at 0x80 and the Rot/vadd/vsub block now matches except the lw g100 position. Left: sched2 gives the g100 lw prio 6 (lw->asm->por->call) vs 10 for the Rot reload lqc2s, so it issues after vadd (target: before lqc2 0x30, then por before vmulax); the lw also has an anti-dep on v0 (high of D_002DDF40), same as target. VU_FLOAT local before d: 13 (same). 1-arg volatile ctor in the gather (d in memory): 28. Else branch: vsub vf3 output (target) suggests an earlyclobber Sub, but "=&j" gives vF0 vf3 (18).
// v9 (Claude agent, laneC23 2026-10-23): aligned 20 -> 17. Rot's v input tied to the output ("0"(v), %0 for v): target vmaddz writes v's register (vF0 vf2); that alone gave 18 and fixed the gather-loop Rot VF numbering. The 1-arg VU_FLOAT ctor (else branch) made volatile: 17 (else-branch lw/vsub/por order closer). Left: if-branch lqc2 order (vF0 not first) and lw g100 position (target issues it before the Rot asm; our 2-arg ctor depends on d), else-branch vsub vf2 vs vf3. Tried: alloc-only d uses in a new empty asm before func_0014F898 (30), VU_FLOAT local before d (30-31), VU_FLOAT local in else (18).
// v8 (Claude agent, laneC22 2026-10-23): aligned 36 -> 20. On top of v7: the VIF loop indexes aLight[i] (loop.c strength-reduces it and puts the pl init after the cLight test, s3 like the target), and `int ten = 10;` is used for both the as[1] multiply and the last func_00226F28 argument (target shares the 10 in t1). Left: the gather-loop VU block (Rot input VF numbering; the target evaluates VU_FLOAT before the Rot asm, ours after vsub because the allocation-only "j"(d) operands make it depend on d) and the else-branch vsub/lw g100 order.
// v7 (Claude agent, laneC22 2026-10-23): aligned 41 -> 36. Gather loop written with gotos only (top: ... next: plo = plo->x128; if (plo) goto top;): no loop for loop.c to hoist from, and the target do/while layout. Two allocation-only "j"(d) operands on the VU_FLOAT empty asm (2-arg ctor used in the loop) give d enough refs for caller-save in vf1.
// v5 (Claude agent, laneC11 2026-10-23): aligned 46 -> 42. ONE commented pin in the else branch: `register CM *pcm asm("$4") = &D_002DDF40;` used for both the call arg and pcm->pos (target builds &D_002DDF40 in a0, giving the beql/bnel + lui a0 slots at the top). An unpinned inline FInside(CM *pcm, ...) wrapper: no change (46, pcm in v1 then copied). Left: else-branch vsub VF numbering / sq order, loop issues as in v4.
// v4 (Claude agent, laneC9 2026-10-23): aligned 66 -> 46. Logic fixes: else branch has no cLight = 0 (target jumps straight to the FRAME dtor/return when func_0014F850 fails: goto none), light loop is for (i = 0; i < cLight; i++) (gcc reverses it: blez entry + bnez), func_0013A688(p) before c++. Left: pl/pb s3/s4 swap, d in memory, pdma/save slots 0x80 vs 0x70, beql slots (&D_002DDF40 in a0).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[3]; float x30, y30, z30, w30; };
struct FRAME { int a[4]; };
struct AL { int cb; int align; AL(int c, int a) { cb = c; align = a; } };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { /* volatile (Claude agent): keeps the else-branch g100 move before the vsub like the target */ __asm__ volatile("" : "=r"(q) : "0"(*(int *)&f)); } VU_FLOAT(float f, int) { __asm__("" : "=r"(q) : "0"(*(int *)&f)); } /* non-volatile 1-arg form for the gather loop (Claude agent) */
    VU_FLOAT(float f, qword d) { __asm__ volatile("" : "=r"(q) : "0"(*(int *)&f), "j"(d), "j"(d)); } };
struct DL { void *head; void *tail; int ibDle; };
struct LO;
struct EX { int pad[2]; struct LO **pplo; };
struct LO { char pad[0x10]; LO *x10; char pad14[0x38 - 0x14]; float g38; char pad3C[0xE4 - 0x3C]; EX *xE4; char padE8[0x11C - 0xE8]; LO *x11C; char pad120[8]; LO *x128; };
struct BUF { qword a[0x2B]; qword b[0x2B]; qword c[0x2B]; char pad[0x840 - 0x810]; };
struct Q { BUF abuf[2]; int i; int c; int pad[2]; Q *pqNext; };
struct P { char pad[0xE0]; LO *xE0; char padE4[0xF0 - 0xE4]; qword vF0; float g100; char pad104[0x43C - 0x104]; int x43C; int pad440[2]; Q *pqFirst; };
struct DMA { int x0; int x4; int x8; int xC; };
struct VIFS { int pad[3]; int xC; };
struct CM { char pad[0x90]; qword pos; };
extern "C" {
extern M3 D_002A2D00;
extern M4 D_002A2D30;
extern CM D_002DDF40;
extern VIFS D_002DEA28;
extern char D_vu0[];
extern char D_vu1[];
extern char D_vu2[];
void func_001AE478(FRAME *pf);
void func_001AE4A0(FRAME *pf, int n);
int func_0011A3B0(void *pdl);
int func_0011A3C0(void *pdl);
void *func_001AE318(const AL &al);
int func_001A61A0(LO *plo);
qword func_001A62E8(LO *plo);
M3 *func_001A6318(LO *plo);
int func_0014F850(CM *pcm, qword d, VU_FLOAT r);
int func_0014F898(CM *pcm, qword d, float g, float *pg);
void func_00256D18(void *pv, qword v);
DMA *func_001CD998(void);
void func_001574B8(VIFS *p);
void func_0013A688(P *p);
void func_00226F28(VIFS *p, ...);
void func_00226D40(VIFS *p, int a, int b);
void func_00227010(VIFS *p, int a, int c, void *pv, int addr, int flag);
void func_00226CE0(VIFS *p, void *pv);
void func_00226D10(VIFS *p);
void func_001576F0(VIFS *p);
void func_00157620(VIFS *p);
void func_0013A1E8(P *p);
}
static inline void *PvAllocStack(int cb) { return func_001AE318(AL(cb, 0x10)); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
/* earlyclobber output (target vsub vf3 distinct from its inputs); the 2nd "j"(b) is allocation-only (Claude agent) */
static inline qword SubE(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=&j"(r) : "j"(a), "j"(b), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword RotK(const M3 &m, qword v, qword k)
{
    qword r;
    /* "r"(k): allocation-only (Claude agent), orders the VU_FLOAT before the Rot like the target */
    __asm__("vmulax.xyz $ACC, %1, %0x\n\tvmadday.xyz $ACC, %2, %0y\n\tvmaddz.xyz %0, %3, %0z" : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "0"(v), "r"(k));
    return r;
}
static inline qword Rot(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %0x\n\tvmadday.xyz $ACC, %2, %0y\n\tvmaddz.xyz %0, %3, %0z" : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "0"(v));
    return r;
}

void func_0013A1E8(P *p)
{
    FRAME frame;
    func_001AE478(&frame);
    int cLight;
    M4 *aLight;
    if (p->xE0 != 0 && func_0011A3B0(&p->xE0->x11C) == 0) {
        cLight = 0;
        aLight = (M4 *)PvAllocStack(func_0011A3C0(&p->xE0->x11C) << 6);
        M4 *pl = aLight;
        LO *plo = p->xE0->x11C;
        M3 *pmId;
        if (!plo) goto done;
        pmId = &D_002A2D00;
    top:
            if (!func_001A61A0(plo))
                goto next;
            {
            LO **pplo = plo->xE4->pplo;
            qword pos;
            M3 mat;
            if (*pplo) {
                pos = func_001A62E8(*pplo);
                mat = *func_001A6318(*pplo);
            } else {
                pos = func_001A62E8(plo);
                if (plo->x10)
                    mat = *func_001A6318(plo->x10);
                else
                    mat = *pmId;
            }
            VU_FLOAT vf(p->g100, 0);
            qword d = Sub(Add(RotK(mat, p->vF0, vf.q), pos), D_002DDF40.pos);
            __asm__("" : "+j"(d)); /* empty asm (Claude agent): extra refs so d is caller-saved in vf1, without making the VU_FLOAT depend on d */
            if (!func_0014F850(&D_002DDF40, d, vf))
                goto next;
            float g;
            if (!func_0014F898(&D_002DDF40, d, plo->g38, &g))
                goto next;
            func_00256D18(&pl->x30, pos);
            cLight++;
            pl->r[0] = mat.r[0];
            pl->r[1] = mat.r[1];
            pl->r[2] = mat.r[2];
            pl->w30 = 1.0f;
            ((int *)&pl->r[2])[3] = 0;
            ((int *)&pl->r[1])[3] = 0;
            ((int *)&pl->r[0])[3] = 0;
            pl++;
            }
        next:
            plo = plo->x128;
            if (plo) goto top;
    done:;
    } else {
        register CM *pcm asm("$4") = &D_002DDF40; /* register pin (Claude agent): target builds &D_002DDF40 in a0 */
        qword v = p->vF0;
        __asm__("" : "+j"(v)); /* empty asm (Claude agent): keeps vF0 in a pseudo */
        VU_FLOAT vf(p->g100);
        if (!func_0014F850(pcm, SubE(v, pcm->pos), vf))
            goto none;
        cLight = 1;
        aLight = &D_002A2D30;
    }
    if (cLight == 0) {
    none:
        func_001AE4A0(&frame, 2);
        return;
    }
    int c = 0;
    DMA *pdma = func_001CD998();
    pdma->x0 = 0xC;
    pdma->x4 = 0;
    int save = D_002DEA28.xC;
    func_001574B8(&D_002DEA28);
    for (Q *pq = p->pqFirst; pq; pq = pq->pqNext) {
        BUF *pb = &pq->abuf[pq->i];
        for (int i = 0; i < cLight; i++) {
            if (c < 2) {
                func_0013A688(p);
                c++;
            }
            unsigned short as[3];
            as[0] = 0x34;
            int ten = 10;
            as[1] = pq->c * ten + 0x34;
            as[2] = pq->c;
            func_00226F28(&D_002DEA28, 9, 1, as, 0, ten);
            func_00226F28(&D_002DEA28, 0xC, 4, &aLight[i], 7);
            func_00226D40(&D_002DEA28, 1, 10);
            if (p->x43C == 1)
                func_00227010(&D_002DEA28, 0xC, pq->c, pb->b, as[0] + 1, 0);
            func_00227010(&D_002DEA28, 0xC, pq->c, pb->c, as[0] + 2, 0);
            func_00227010(&D_002DEA28, 0xC, pq->c, pb->a, as[0] + 3, 0);
            func_00226D40(&D_002DEA28, 1, 1);
            switch (p->x43C) {
            case 0: func_00226CE0(&D_002DEA28, D_vu0); break;
            case 1: func_00226CE0(&D_002DEA28, D_vu1); break;
            case 2: func_00226CE0(&D_002DEA28, D_vu2); break;
            }
            func_00226D10(&D_002DEA28);
        }
    }
    func_001576F0(&D_002DEA28);
    func_00157620(&D_002DEA28);
    pdma->x8 = save;
    func_001AE4A0(&frame, 2);
}
