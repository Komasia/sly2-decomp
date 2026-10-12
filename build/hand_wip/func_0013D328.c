struct C { int a[4]; };
struct CRef { int m_tagk; int m_n; };
struct S { char pad[0x194]; void *f194; };
extern char D_003D4A60[];
void func_0013C560(void *, int);
void func_001AE478(struct C *);
void func_001AE4A0(struct C *, int);
void *func_0013D1A8(struct S *);
void func_001291A8(struct CRef *, struct CRef *);
void func_00258200(struct CRef *, void *, struct CRef *, void *);
void func_00129EC8(struct CRef *);
void func_0013CF38(struct S *, int);
void func_0013D328(struct S *p, int n) {
    struct C ctx;
    struct CRef ref;
    void *pv;
    if (p->f194) func_0013C560(p->f194, 0);
    func_001AE478(&ctx);
    pv = func_0013D1A8(p);
    ref.m_tagk = 0x15;
    ref.m_n = n;
    {
        struct CRef ref2;
        struct CRef ref3;
        func_001291A8(&ref2, &ref);
        func_00258200(&ref3, pv, &ref2, D_003D4A60);
        func_00129EC8(&ref3);
        func_00129EC8(&ref2);
    }
    func_00129EC8(&ref);
    if (n != -1) func_0013CF38(p, 0);
    func_001AE4A0(&ctx, 2);
}
