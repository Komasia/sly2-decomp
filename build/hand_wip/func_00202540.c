/* wip: 12 diffs. Unknown idiom: target passes x->fE0 as qword arg via 'lw v0; por a2,v0; sq v0,0(sp)' (value in GPR + dead store to a stack slot); also pos should be a stack union (sq after call, lqc2 reload). Same idiom in func_0020A818 (with 0.0f). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct VE { short d; short pad; void (*pf)(void *, void *); };
struct O { char pad[0xC]; struct VE *vt; };
struct X { char pad[0x38]; float f38; char pad2[0xE0 - 0x3C]; float fE0; char pad3[0x108 - 0xE4]; int k108; };
struct S { char pad[0x20]; char a20[8]; float f28; int pad2; int c; struct X *ax[1]; };
struct S2 { char pad[0x8C]; struct X *sel; char pad2[0xA8 - 0x90]; struct O **ppo; };
struct G { char pad[0x90]; qword pos; };
extern struct G D_002DDF40;
extern float D_002A8550;
int func_00203790(struct X *x);
qword func_001A62E8(void *p);
int func_0014F850(struct G *g, qword d, qword u);
int func_0014F898(struct G *g, qword pos, qword *pq, float f);
void func_00202378(void *p, struct X *x);
void func_00202768(void *p, int n);

void func_00202540(struct S *p)
{
    struct O *po = *((struct S2 *)p)->ppo;
    float best;
    struct X *sel = 0;
    int i;
    po->vt[97].pf((char *)po + po->vt[97].d, p->a20);
    p->f28 += 20.0f;
    best = D_002A8550;
    for (i = 0; i < p->c; i++) {
        struct X *x = p->ax[i];
        struct G *g;
        qword pos, d, tmp;
        U u;
        float dist;
        if (!func_00203790(x))
            continue;
        pos = func_001A62E8(x);
        g = &D_002DDF40;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(g->pos));
        u.f = x->fE0;
        if (!func_0014F850(g, d, u.q))
            continue;
        if (!func_0014F898(g, func_001A62E8(x), &tmp, x->f38))
            continue;
        __asm__("vsub.xyzw %0, %1, %2\n\tvmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(pos), "j"(g->pos));
        __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(d));
        if (dist < best) {
            func_00202378(p, x);
            if (x->k108 != 2) {
                sel = x;
                best = dist;
            }
        }
    }
    if (sel != ((struct S2 *)p)->sel) {
        ((struct S2 *)p)->sel = sel;
        func_00202768(p, 2);
    }
}
