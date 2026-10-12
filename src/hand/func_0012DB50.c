typedef struct T { int a; int b; int c; int d; int e; int f; } T;
T *func_0012E238(void *p);
T *func_0012DB50(void *p, int b, int c, int d, int f)
{
    T *t = func_0012E238(p);
    t->b = b;
    t->c = c;
    t->d = d;
    t->f = f;
    return t;
}
