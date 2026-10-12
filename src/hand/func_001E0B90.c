typedef struct S { char pad[0x10]; int a; float f; float g; int c; int d; int e; } S;
S *func_001E01F8(void *p, int cb);
void func_001E0B90(void *p, int a, int b, int c, int d, float f, float g)
{
    S *s = func_001E01F8(p, 0x24);
    s->a = a;
    s->f = f;
    s->g = g;
    s->c = c;
    s->d = d;
    s->e = 1;
}
