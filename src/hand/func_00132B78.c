struct S { int f0; int f4; };
int PsidebagNew__Fv(void);
void func_002580A8(int *, int);
void func_00258178(int);
void EnsureBasicSidebag__FP5BASIC(struct S *p) {
    int *pf = &p->f4;
    if (p->f4 == 0) { func_002580A8(pf, PsidebagNew__Fv()); func_00258178(p->f4); }
}
