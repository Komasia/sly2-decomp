/* WIP 15/88: structure right incl. nops; remaining: regalloc (i in a0 vs v1, qmfc2 out v0 vs a0) and the 7/9 path order (target loads o->x70 before f; looks like Lin() inlined in both branches + cross-jumped, see notes). */
typedef int qword __attribute__((mode(TI)));
struct E0 { int x0, x4; float x8; };
struct LO { char pad[0x70]; qword x70; };
struct E { struct E0 *x0; struct LO *x4; int x8; int xC; qword x10; qword x20; qword x30; };
struct P { struct E e[2]; qword x80; float x90; int pad[2]; int x9C; };
qword func_0022FC48(struct LO *p, int n, qword q);
static __inline__ qword Lin(qword a, qword b, int f)
{
    union { qword q; float f; } t;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(t.q) : "r"(f));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(t.q));
    return r;
}
void func_001A7E60(void *unused, int n, struct P **ap)
{
    int i;
    for (i = 0; i < n; i++) {
        struct P *p = ap[i];
        struct E *e;
        int j;
        e = p->e;
        for (j = 0; j < 2; j++, e++) {
            struct LO *o = e->x4;
            if (!o)
                continue;
            {
            int f;
            union { float f; int i; } u;
            if (j == 0) {
                switch (p->x9C) {
                case 4: case 5: case 6:
                    u.f = -e->x0->x8; f = u.i;
                    break;
                default:
                    goto def;
                }
            } else {
                switch (p->x9C) {
                case 7: case 9:
                    f = *(int *)&e->x0->x8;
                    break;
                default:
                    goto def;
                }
            }
            e->x10 = Lin(o->x70, p->x80, f);
            continue;
            }
        def:
            e->x10 = func_0022FC48(o, 0, e->x20);
        }
        {
            qword d, r, one;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(p->e[0].x10), "j"(p->e[1].x10));
            __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=&j"(one) : "j"(p->x80), "j"(d));
            { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r)); __asm__("sw %1, %0" : "=m"(p->x90) : "r"(g)); }
        }
    }
}
