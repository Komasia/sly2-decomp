typedef struct S { char pad[0x10]; int a; int b; int c; float f; int d; int e; } S;
S *func_001E01F8(void *p, int k, int n);
void func_001E0CB8(void *p, int a, int b, int c, int d, int e, float f)
{
    S *s = func_001E01F8(p, 0x27, 0);
    s->a = a;
    s->b = b;
    s->c = c;
    s->f = f;
    s->d = d;
    s->e = e;
}
