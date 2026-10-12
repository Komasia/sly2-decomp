struct E { char pad[8]; short h8; short pad2; float fC; int x10; void *x14; };
struct S { char pad[8]; struct E *ae; char padc[4]; unsigned long ul10; float f18; int x1C; int x20; };
extern unsigned long D_002DDF18;
void func_001FB098(void *p, float f);
void func_00258040(void **pp, int n);
void func_00217F38(struct S *p, int i);
static inline void Release(void **pp)
{
    if (pp && *pp) {
        func_001FB098(*pp, 0.0f);
        func_00258040(pp, 0);
    }
}
void func_00218660(struct S *p, int i)
{
    struct E *e = &p->ae[i];
    if (e->h8 >= 0) {
        p->x1C = e->h8;
        p->f18 = e->fC;
        p->ul10 = D_002DDF18;
        p->x20 = -1;
        e->h8 = -1;
        e->x10 = 0;
        Release(&e->x14);
    }
    func_00217F38(p, i);
}
