struct S { char pad[0x184]; int n; char p1[0x38]; int x1c0; };
extern char D_002DEB30[];
int func_0017F1D0(struct S *p);
void func_001619A0(void *g, int n, struct S *p);
void func_00181268(struct S *p, int n);
int func_001811B8(struct S *p)
{
    if (p->x1c0 == 4) return 0;
    if (!func_0017F1D0(p)) return 0;
    if (p->n < 0) return 1;
    if (p->n <= 0) func_001619A0(D_002DEB30, 0x18, p);
    func_00181268(p, 4);
    return 1;
}
