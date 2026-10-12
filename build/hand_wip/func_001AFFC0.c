/* 23/45 differ: target hoists xC/x0 but reloads x8 each iter, no strength reduction, first iteration peeled */
struct S { int x0; int x4; int x8; int *xC; int pad[3]; int x1C; };
extern char D_003D9ED0[];
void func_001AFB88(void *g, struct S *s);
void func_001AFFC0(struct S *s)
{
    int i;
    for (i = 0; i < s->x8; i++) { if (s->x0 == s->xC[i]) break; } if (i < s->x8) s->x0 = s->xC[(i + 1) % s->x8];
    func_001AFB88(D_003D9ED0, s);
    s->x1C |= 2;
}
