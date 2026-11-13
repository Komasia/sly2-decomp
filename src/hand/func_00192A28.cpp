typedef int qword __attribute__((mode(TI)));
extern "C" {
void __10STACKSCOPE(void *p);
void _$_10STACKSCOPE(void *p, int n);
void *PdetentryFind(void *a, void *b) asm("PdetentryFind__FP8DETECTORi");
void SetDetentryState(void *a, void *b, int c) asm("SetDetentryState__FP8DETECTORP8DETENTRYi");
qword PosOfLo(void *p) asm("PosOfLo__FP2LO");
void func_0020FAA0(void *g, qword a, qword b, void *pfn, void *o, int *pi, int *pj);
int PsoHitTestLineObjects(int z, qword a, qword b, int i, int j, int k) asm("PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG");
void func_00154568(void);
extern char g_sw[];
extern float D_002BF638;
}
class FRAME { public: FRAME() { __10STACKSCOPE(this); } ~FRAME() { _$_10STACKSCOPE(this, 2); } };
struct E { int x0; int x4; };
struct F { char pad[0xF8]; int xf8; };
struct O { char pad[0xF64]; F *xf64; char pad2[0xFE0 - 0xF68]; O *xfe0; };
extern "C" O *D_003E1444;
struct P { void *x0; };
extern "C" void ForgetGuardsInteract(P *p) asm("ForgetGuardsInteract__FP5ACTOR");
// name: SafeHouse port (ForgetGuardsInteract)
void ForgetGuardsInteract(P *p)
{
    O *o;
    for (o = D_003E1444; o; o = o->xfe0) {
        E *e = (E *)PdetentryFind(o->xf64, p->x0);
        if (!e || !e->x4 || (o->xf64->xf8 & 1)) continue;
        qword a = PosOfLo(o);
        qword b = PosOfLo(p->x0);
        qword d, t;
        float dist;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d), "=&j"(t));
        __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(d));
        bool far = D_002BF638 < dist;
        if (far) {
            SetDetentryState(o->xf64, e, 0);
            continue;
        }
        struct { char c; FRAME frame; int i, j; } x;

        func_0020FAA0(g_sw, a, b, (void *)func_00154568, o, &x.i, &x.j);
        if (!PsoHitTestLineObjects(0, a, b, x.i, x.j, 0)) continue;
        SetDetentryState(o->xf64, e, 0);
    }
}
