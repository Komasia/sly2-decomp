typedef int qword __attribute__((mode(TI)));
typedef struct R { char pad[0x1C]; int x1C; qword v; } R;
R *func_0012DB50(int k, void *a, void *b, void *c, int d);
void AddXfCtrl__FP3ALOP2XFP4CTRL(void *a, void *b, void *p);
// name: SafeHouse port (PctrlNewPos)
R *PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(void *a, void *b, void *c, int d, int e, qword v)
{
    R *p = func_0012DB50(1, a, b, c, d);
    p->x1C = e;
    p->v = v;
    AddXfCtrl__FP3ALOP2XFP4CTRL(a, b, p);
    return p;
}
