typedef int qword __attribute__((mode(TI)));
struct T { char pad[0xF8]; int xF8; };
struct SO;
struct AL { int cb; int cbAlign; AL(int c, int a) { cb = c; cbAlign = a; } };
extern "C" {
void __10STACKSCOPE(void *p);
void _$_10STACKSCOPE(void *p, int n);
qword PosDetectorEye(T *p) asm("PosDetectorEye__FP8DETECTOR");
void *PvAllocStackImpl(AL *pal) asm("PvAllocStackImpl__Fi");
qword ConvertPos(SO *pso, int z, qword v) asm("ConvertPos__FP2LOT0G9VU_VECTOR");
void func_0020FAA0(void *g, qword a, qword b, void *pfn, void *o, int *pi, int *pj);
int func_0014CC58(int z, qword a, qword b, int i, int j, int k);
void func_00154568(void);
void func_00154528(void);
extern char g_sw[];
extern qword D_002BDBF0[];
int FSightBlocked(T *p, SO *pso) asm("FSightBlocked__FP8DETECTORP2LO");
}
class FRAME { public: FRAME() { __10STACKSCOPE(this); } ~FRAME() { _$_10STACKSCOPE(this, 2); } };


// name: SafeHouse port (FSightBlocked)
int FSightBlocked(T *p, SO *pso)
{
    FRAME frame;
    int i;
    qword *ppos = D_002BDBF0;
    qword q = PosDetectorEye(p);
    AL al(0x10, 0x10);
    qword *apos = (qword *)PvAllocStackImpl(&al);
    int ii, jj;
    qword vmax = q;
    qword vmin = q;
    for (i = 0; i < 1; i++) {
        qword t = ConvertPos(pso, 0, ppos[i]);
        apos[i] = t;
        __asm__("vmini.xyz %0, %0, %1" : "+j"(vmin) : "j"(t));
        __asm__("vmax.xyz %0, %0, %1" : "+j"(vmax) : "j"(t));
    }
    void *pfn = (void *)func_00154568;
    if (p->xF8 & 4) pfn = (void *)func_00154528;
    func_0020FAA0(g_sw, vmin, vmax, pfn, p, &ii, &jj);
    bool f;
    for (i = 0; (f = i < 1); i++)
        if (!func_0014CC58(0, q, apos[i], ii, jj, 0)) break;
    return !f;
}
