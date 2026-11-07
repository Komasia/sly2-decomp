typedef int qword __attribute__((mode(TI)));
struct S;
typedef struct { short d; short pad; int (*pfn)(); } VT;
struct S { int x0, x4, x8; VT *vt; char pad[0x150 - 0x10]; int k; int x154; int x158; char pad2[0x16C - 0x15C]; struct S *pt; float r; char pad3[0x1A0 - 0x174]; int x1A0; };
void UpdateSo__FP2SOf(struct S *p);
void LandCarry__FP2LOT0(struct S *p, int a);
qword func_001A62E8(struct S *p);
// name: SafeHouse port (UpdateCarry)
void UpdateCarry__FP2LO(struct S *p)
{
    UpdateSo__FP2SOf(p);
    if (p->k == 1 && p->x158 != -1)
        LandCarry__FP2LOT0(p, p->x1A0);
    if (p->pt) {
        qword a = func_001A62E8(p);
        qword b = func_001A62E8(p->pt);
        qword d, t, l;
        float g;
        int f;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(t) : "0"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
        f = p->r < g;
        if (f)
            p->vt[75].pfn((struct S *)((char *)p + p->vt[75].d), 0);
    }
}
