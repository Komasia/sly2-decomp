struct S { int f0; int f4; };
int func_00257D80(void);
void func_002580A8(int *, int);
void func_00258178(int);
void func_00132B78(struct S *p) {
    int *pf = &p->f4;
    if (p->f4 == 0) { func_002580A8(pf, func_00257D80()); func_00258178(p->f4); }
}
