typedef struct E { int n; float x; float y; float g; float h; } E;
typedef struct T { char pad[0xE4]; int c; E *a; } T;
void func_0012EEE0(T *t, int n, int x, int y, float g, float h)
{
    if (t->c < 8) {
        E *e = &t->a[t->c++];
        e->n = n;
        e->x = x;
        e->y = y;
        e->g = g;
        e->h = h;
    }
}
