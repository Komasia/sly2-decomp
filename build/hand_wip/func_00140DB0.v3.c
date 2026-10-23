/* v3 (Claude agent, laneC10 2026-10-23): aligned 7 -> 6 with ONE register pin (k in $8/t0 like the target) and save.q = s->v before the kk load. Left: the D_002E1E40 load (and its lui) still sinks to just before the first beq; target loads it at the very top. volatile D_002E1E40 with the pin: 8; pe pointer with the pin: 11. */
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
    register int k asm("$8"); /* register pin (Claude agent): target keeps k in t0 */
    int kk;
    k = D_002E1E40;
    save.q = s->v;
    kk = s->ae[1 - i].k;
    if (kk == k || kk == D_002DD5BC || kk == D_002F7900) {
        if (p->p150->x80 != 1 || func_00144068(p)) {
            register qword vs __asm__("vf3") = save.q;
            register qword vo __asm__("vf2");
            __asm__("qmtc2.ni %1, %0" : "=j"(c.q) : "r"(0.01f));
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(vo) : "j"(vs), "j"(c.q));
            s->v = vo;
        }
    }
    func_001FAD00(p, a, s, b, i);
    s->v = save.q;
}
