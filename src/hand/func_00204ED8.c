typedef int qword __attribute__((mode(TI)));
typedef struct { short d; short pad; void *pfn; } VTE;
extern qword D_002A2DD0;
struct O { VTE *vt; };
struct X { int a; struct O *po; };
struct Q { char pad[0x14]; int n14; char pad2[0x40 - 0x18]; float g40; };
int func_00131968(struct Q *q);
struct X *func_0012FF10(int n, void *p, int a, int b);
qword func_00204ED8(void *p, struct Q *q, float g)
{
    qword r = D_002A2DD0;
    if (q && !func_00131968(q)) {
        struct X *x = func_0012FF10(q->n14, p, 6, 1);
        if (x) {
            struct O *o = x->po;
            ((void (*)(void *, int, qword *, float, float))o->vt[3].pfn)((char *)o + o->vt[3].d, 0, &r, g, q->g40);
        }
    }
    return r;
}
