// v5 (Claude agent, laneC38 2026-10-24): aligned 6 like v3 but with NO register pin. Rewritten in Lilly's style: VuFloat (qmtc2 asm) + QwScaleX helpers, the plo/D_002E1E40 compare as LO pointers read first into a local (k now gets t0 without the pin), the VU_FLOAT kept in a union local so it is stored to 0x0 like the target. Left: the lui/lw of D_002E1E40 at the top (target issues them among the register saves, using a2 after its copy).
typedef int qword __attribute__((mode(TI)));
struct LO;
struct E { int a, b; struct LO *plo; char pad[0x34]; };
struct S { char pad[0x40]; qword v; struct E *ae; };
struct X150 { char pad[0x80]; int x80; };
struct P { char pad[0x150]; struct X150 *p150; };
struct VU_FLOAT { qword qw; };
extern struct LO *D_002E1E40;
extern struct LO *D_002DD5BC;
extern struct LO *D_002F7900;
int func_00144068(struct P *p);
void func_001FAD00(struct P *p, void *a, struct S *s, void *b, int i);
static inline struct VU_FLOAT VuFloat(float g)
{
    struct VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline qword QwScaleX(qword qwVec, struct VU_FLOAT g)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(qwVec), "j"(g.qw));
    return qw;
}
void func_00140DB0(struct P *p, void *a, struct S *s, void *b, int i)
{
    struct LO *plo0 = D_002E1E40;
    qword vSave = s->v;
    struct LO *plo = s->ae[1 - i].plo;
    if (plo == plo0 || plo == D_002DD5BC || plo == D_002F7900) {
        if (p->p150->x80 != 1 || func_00144068(p)) {
            union { struct VU_FLOAT vf; float f[4]; } c;
            c.vf = VuFloat(0.01f);
            s->v = QwScaleX(vSave, c.vf);
        }
    }
    func_001FAD00(p, a, s, b, i);
    s->v = vSave;
}
