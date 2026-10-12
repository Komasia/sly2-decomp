typedef struct T { int a[7]; void *q; } T;
typedef struct Q { int pad[2]; void *b; } Q;
T *func_0012DB50(int k, void *a, void *b, void *c, int d);
void func_00230018(void *a, void *b, T *p);
T *func_0012DD28(void *a, void *b, void *c, Q *q)
{
    T *p = func_0012DB50(7, a, b, c, b == q->b ? 0xE : 0xD);
    p->q = q;
    func_00230018(a, b, p);
    return p;
}
