typedef struct E { int n; float x; float y; float g; } E;
typedef struct T { char pad[0xF0]; int c; E *a; } T;
void func_0012EF40(T *t, int n, int x, int y, float g)
{
    if (t->c < 8) {
        E *e = &t->a[t->c++];
        e->g = g;
        e->n = n;
        e->x = x;
        e->y = y;
    }
}
