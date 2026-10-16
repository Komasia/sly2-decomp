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
    int k, kk;
    k = D_002E1E40;
    kk = s->ae[1 - i].k;
    save.q = s->v;
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
