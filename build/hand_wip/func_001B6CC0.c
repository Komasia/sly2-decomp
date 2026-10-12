typedef int qword __attribute__((mode(TI)));
struct VT { short d; short pad; void *pfn; };
struct O { char pad[0x80]; qword v80; };
struct P {
    char pad0[0xC]; struct VT *vt; char pad1[0xE8 - 0x10]; struct O *pE8; char pad1b[0x190 - 0xEC]; qword v190;
    char pad4[0x13D8 - 0x1A0]; int x13D8;
};
extern qword D_002A2DC0;
extern float D_002C09A4;
void func_001FAC30(struct P *p, qword v);
typedef union { qword q; float f[4]; } U;
static inline qword Scale(qword a, float g) { U u; qword k, r; __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(g)); __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(k)); u.q = k; return r; }
static inline qword ScaleI(qword a, int g) { union { qword q; int i[4]; } u; qword k, r; __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(g)); __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(k)); u.q = k; return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword MulX(qword a, qword k) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(k)); return r; }
static inline qword Dot(qword a, qword b) { qword r, one; __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(r), "=&j"(one) : "j"(a), "j"(b)); return r; }
void func_001B6CC0(struct P *p)
{
    switch (p->x13D8) {
    case 0:
        func_001FAC30(p, Scale(p->pE8->v80, -1.0f));
    case 1: {
        qword v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);
        qword d = Sub(Scale(p->v190, -1.0f), v);
        qword up = D_002A2DC0;
        d = Sub(d, MulX(up, Dot(d, up)));
        func_001FAC30(p, ScaleI(d, *(int *)&D_002C09A4));
        break;
    }
    case 2:
        break;
    }
}
