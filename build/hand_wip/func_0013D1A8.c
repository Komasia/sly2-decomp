struct P { int c; short *as; };
struct S { char pad[0x180]; unsigned short f180; };
struct T { int pad[2]; int f8; };
extern struct T D_003E0EA8;
extern char D_002A4BB8[];
extern char D_002A4BC0[];
int func_00210A88(void);
short func_001D8720(void *, char *);
void *func_002109B8(int);
void func_001D8CC8(void *, struct P *);
void func_0013D1A8(struct S *p) {
    short as[3];
    struct P par;
    int i = 0;
    int v = func_00210A88();
    void *pv;
    if (v != -1) i = v;
    pv = &D_003E0EA8.f8;
    as[0] = func_001D8720(pv, D_002A4BB8);
    as[1] = func_001D8720(pv, D_002A4BC0);
    as[2] = p->f180;
    par.c = 3;
    par.as = as;
    func_001D8CC8(func_002109B8(i), &par);
}
