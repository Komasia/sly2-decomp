typedef struct E { int a; int k; int n; int b; } E;
typedef struct T { char pad[0xA0]; int c; E *a; } T;
E *func_0012F938(T *t, int n)
{
    int i;
    E *e;
    for (i = 0; i < t->c; i++) {
        e = &t->a[i];
        if ((e->k == 0xB) & (e->n == n))
            return e;
    }
    return 0;
}
