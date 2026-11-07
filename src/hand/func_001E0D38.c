typedef struct S { char pad[0x10]; int a; float f; int b; float g; int c; int d; } S;
S *PcmdNew__FP4SCPTii(void *p, int k, int n);
void func_001E0D38(void *p, int a, float f, int b, float g, int c, int d)
{
    S *s = PcmdNew__FP4SCPTii(p, 0x28, 0);
    s->a = a;
    s->f = f;
    s->b = b;
    s->g = g;
    s->c = c;
    s->d = d;
}
