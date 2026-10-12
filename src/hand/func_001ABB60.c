struct S { char pad[0xFD50]; void *x; };
extern char D_002E6550[];
void *func_001AC598(struct S *s);
void *func_001AB7D0(struct S *s);
void *func_001AC420(struct S *s, void *x);
void func_001ACC38(void *p, int n);
void *func_001ABB60(struct S *s)
{
    void *p = func_001AC598(s); if (!p) p = func_001AB7D0(s); if (!p) p = func_001AC420(s, s->x); if (p) func_001ACC38(D_002E6550, 3); return p;
}
