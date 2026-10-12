typedef int qword __attribute__((mode(TI)));
typedef struct VT { short d; short pad; void (*pfn)(void *); } VT;
typedef struct O { char pad[0x18]; VT *vt; } O;
typedef struct SW { char pad[0xC0]; qword a; char pad2[0x10]; qword b; } SW;
typedef struct T2 { char pad[8]; SW *psw; char pad1[0x10]; O *po; qword v; } T2;
void func_0012CF28(T2 *p);
static __inline__ void AddV(qword *pd, qword *ps)
{
    register qword b __asm__("vf2") = *ps;
    register qword a __asm__("vf1") = *pd;
    __asm__ ("vadd.xyzw %0, %0, %1" : "+j"(a) : "j"(b));
    *pd = a;
}
void func_0012D958(T2 *p)
{
    O *po = p->po;
    if (po) {
        ((void (*)(void *))po->vt[4].pfn)((char *)po + po->vt[4].d);
        AddV(&p->psw->a, &p->v);
        AddV(&p->psw->b, &p->v);
    } else {
        func_0012CF28(p);
    }
}
