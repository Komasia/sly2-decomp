typedef int qword __attribute__((mode(TI)));
struct S { int a; int k; char pad[0x20]; float r; char pad2[0xB4]; qword e0; char pad3[0x10]; qword p100; qword p110; float t; float f; int g; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
qword func_001A62E8(void *q);
void func_00220508(struct S *p, void *q)
{
    int k = p->k;
    if (k < 7) if (k >= 4) {
        qword v = func_001A62E8(q), a = p->e0, d, r, t;
        float len;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(v));
        p->p110 = v;
        __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=&j"(t) : "0"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(r));
        p->p100 = a;
        __asm__("qmfc2.ni %0, %1" : "=r"(len) : "j"(r));
        {
            float f = len / p->r;
            p->t = D_002DDED0.t;
            p->g = 1;
            p->f = f;
        }
    }
}
