struct E { int a; int b; int c; float g; float t; int z14; int z18; int z1C; int z20; };
struct S { char pad[0x1C0]; int c; struct E a[3]; };
extern char D_003DD040[];
float func_001FE3F8(void *p);
void func_002332B8(void *dst, void *src, int cb);
void func_001532D8(struct S *p, int a, int b, int c, float g)
{
    struct E *pe;
    if (p->c == 3) {
        func_002332B8(&p->a[0], &p->a[1], (p->c - 1) * sizeof(struct E));
        { int i = p->c - 1; pe = &p->a[i]; }
    } else {
        pe = &p->a[p->c] - 1;
    }
    pe->a = a;
    pe->b = b;
    pe->c = c;
    pe->g = g;
    pe->t = func_001FE3F8(D_003DD040);
    pe->z14 = 0;
    pe->z18 = 0;
    pe->z1C = 0;
    pe->z20 = 0;
}
