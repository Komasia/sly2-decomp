typedef struct T { int a[7]; float x; float y; } T;
T *func_0012DB50(int k, void *a, void *b, void *c, void *d);
void func_00230018(void *a, void *b, T *p);
T *func_0012DCA0(void *a, void *b, void *c, void *d, float x, float y)
{
    T *p = func_0012DB50(4, a, b, c, d);
    p->x = x;
    p->y = y;
    func_00230018(a, b, p);
    return p;
}
