typedef struct S { char pad[0x10]; int a; float f; float g; int c; int d; int e; } S;
S *PcmdNew__FP4SCPTii(void *p, int cb);
void func_001E0B90(void *p, int a, int b, int c, int d, float f, float g)
{
    S *s = PcmdNew__FP4SCPTii(p, 0x24);
    s->a = a;
    s->f = f;
    s->g = g;
    s->c = c;
    s->d = d;
    s->e = 1;
}
