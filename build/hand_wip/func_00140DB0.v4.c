/* v4 (Claude agent, laneC22 2026-10-23): ONE pin version, aligned 7 (v3 was 6 with three pins). Pins on k and vo removed; vs stays pinned to vf3. The qmtc2 output goes to a plain qword cq (copied to the union c after the vmulx) with an allocation-only second "j"(cq) operand, so cq gets vf1 first, and the vmulx output is earlyclobber ("=&j") so vo does not tie to vs and gets vf2. The VU block now matches. Left: the D_002E1E40 load (target: lui at the top, lw into t0 right after the i copy; ours v0 just before the beq). Without the k pin: volatile k load 8, plus volatile save/kk reads 13. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct E { int a, b, k; char pad[0x34]; };
struct S { char pad[0x40]; qword v; struct E *ae; };
struct X150 { char pad[0x80]; int x80; };
struct P { char pad[0x150]; struct X150 *p150; };
extern int D_002E1E40;
extern int D_002DD5BC;
extern int D_002F7900;
int func_00144068(struct P *p);
void func_001FAD00(struct P *p, void *a, struct S *s, void *b, int i);
void func_00140DB0(struct P *p, void *a, struct S *s, void *b, int i)
{
    U c, save;
    int k;
    int kk;
    k = D_002E1E40;
    save.q = s->v;
    kk = s->ae[1 - i].k;
    if (kk == k || kk == D_002DD5BC || kk == D_002F7900) {
        if (p->p150->x80 != 1 || func_00144068(p)) {
            register qword vs __asm__("vf3") = save.q; /* register pin (Claude agent): target vs in vf3 */
            qword vo;
            qword cq;
            __asm__("qmtc2.ni %1, %0" : "=j"(cq) : "r"(0.01f));
            __asm__("vmulx.xyzw %0, %1, %2x" : "=&j"(vo) : "j"(vs), "j"(cq), "j"(cq)); /* extra "j"(cq): allocation-only operand */
            s->v = vo;
            c.q = cq;
        }
    }
    func_001FAD00(p, a, s, b, i);
    s->v = save.q;
}
