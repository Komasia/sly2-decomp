typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pf)(); };
struct MAT { qword a[3]; };
struct Q { char pad[0xA0]; void *xA0; };
struct LO { char pad[0xC]; VTE *vt; int x10; char p1[0x58 - 0x14]; Q *x58; Q *x5C; };
struct S { char pad[0x84]; LO *x84; char p1[0x94 - 0x88]; int x94; int x98; int x9C; LO *xA0; };
struct CLOCK { float t; float dt; };
extern CLOCK g_clock;
extern float D_002C1EF4;
extern qword D_002A2DD0;
extern "C" {
void func_001CCAC0(S *p, int n);
void DeleteCtrl(int *p) asm("DeleteCtrl__FPP4CTRL");
void ReparentBooty(LO *p, int a, int b) asm("ReparentBooty__FP3ALOii");
qword func_001A62E8(LO *p);
qword func_0022FC48(int a, void *pv, qword q);
int PctrlNewTarget(LO *p, Q *q, int n, qword a, qword b, float g) asm("PctrlNewTarget__FP3ALOP2XFPvfG9VU_VECTORT4");
void *MatJtLo(LO *p) asm("MatJtLo__FP2LO");
int PctrlNewPos(LO *p, Q *q, int a, int b, int c, qword d) asm("PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR");
void func_001CD308(S *p, LO *po);
}
MAT func_0022FD38(int a, void *pv, void *v);
qword DecomposeEulerMatrix(MAT m) asm("DecomposeEulerMatrix__FP7MATRIX3");
void func_001CD308(S *p, LO *po)
{
    MAT mat;
    int unused[4];
    if (!p->xA0) return;
    func_001CCAC0(p, -1);
    DeleteCtrl(&p->x94);
    DeleteCtrl(&p->x98);
    DeleteCtrl(&p->x9C);
    if (po->x10) {
        
        void *pv = ((void *(*)(void *, void *))po->vt[32].pf)((char *)po + po->vt[32].d, &mat);
        LO *pa = p->xA0;
        ((void (*)(void *, int, void *, int))pa->vt[10].pf)((char *)pa + pa->vt[10].d, po->x10, pv, 0xF);
    } else {
        ReparentBooty(p->xA0, 0, 0xF);
    }
    Q *q = p->xA0->x58;
    p->x94 = PctrlNewTarget(p->xA0, q, 5, func_0022FC48(0, q->xA0, func_001A62E8(po)), D_002A2DD0, g_clock.t + D_002C1EF4);
    q = p->xA0->x5C;
    mat = func_0022FD38(0, q->xA0, MatJtLo(po));
    p->x9C = PctrlNewPos(p->xA0, q, 5, 7, 2, DecomposeEulerMatrix(mat));
    p->x84 = p->xA0;
    func_001CCAC0(p, 1);
    p->xA0 = 0;
}
