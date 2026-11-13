struct S { int a, b, c, d; int f10, f14, f18; };
extern char D_003D4A60[];
extern char D_002DE578[];
extern int D_002E1E00;
void *s1_memset(void *pv, int n, int cb);
void ResetSlotKeepSettings__FPci(void *p, int n);
void func_00154A60(void *p);
void func_001613F8(struct S *p)
{
    s1_memset(p, 0, sizeof(*p));
    p->f10 = -1;
    p->f14 = -1;
    p->f18 = -1;
    ResetSlotKeepSettings__FPci(D_003D4A60, 0);
    func_00154A60(D_002DE578);
    D_002E1E00 = 0;
}
