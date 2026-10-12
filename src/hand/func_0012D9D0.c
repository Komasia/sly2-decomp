typedef int qword __attribute__((mode(TI)));
typedef struct VT { short d; short pad; void (*pfn)(void *); } VT;
typedef struct O { char pad[0x18]; VT *vt; } O;
typedef struct T2 { char pad[0x1C]; O *po; qword v; } T2;
void func_0012D9D0(T2 *p, qword *pv, void *x)
{
    O *po = p->po;
    ((void (*)(void *, qword *, void *))po->vt[5].pfn)((char *)po + po->vt[5].d, pv, x);
    if (pv) {
        register qword b __asm__("vf2") = p->v;
        register qword a __asm__("vf1") = *pv;
        __asm__ ("vadd.xyzw %0, %0, %1" : "+j"(a) : "j"(b));
        *pv = a;
    }
}
