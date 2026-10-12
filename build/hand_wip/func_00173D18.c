typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern float D_002BE5DC;
struct O { char pad[0x28]; unsigned long fl; char pad2[0x84 - 0x30]; float g84; char pad3[0x330 - 0x88]; int n330; };
struct X { char pad[8]; struct O *po; };
struct E { struct O *po; float g4; float g8; struct X *px; int k; int pad[3]; qword pos; };
struct S { char pad[0x5C]; int c; struct E *ae; };
void func_00173928(struct S *p, struct E *pe, int k, int f);
static inline float Dist(qword a, qword b) {
    qword d;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
void func_00173D18(struct S *p, qword pos) {
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *e = &p->ae[i];
        struct O *o = e->po;
        if (!o) {
            if (e->k == 1) {
                int f = D_002BE5DC < Dist(e->pos, pos);
                if (f) {
                    e->k = 0;
                    e->g8 = D_002DDED0.t;
                }
            }
        } else if (o->n330) {
            func_00173928(p, e, 1, 0);
        } else if (!((int)(o->fl >> 60) & 1) || !((int)(e->px->po->fl >> 60) & 1)) {
            func_00173928(p, e, 0, 0);
        } else {
            e->g4 = (e->g4 > o->g84) ? e->g4 : o->g84;
        }
    }
}
