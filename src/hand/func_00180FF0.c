struct E { int a; int b; int x8; char pad[0x34]; };
struct S { char pad[0x188]; int n; };
extern int D_002DFB80;
void func_0017F1A0(struct S *p, struct E *ae, int i);
void func_0017F5B0(struct S *p, int n);
void func_00180FF0(struct S *p, struct E *ae, int i)
{
    func_0017F1A0(p, ae, i);
    if (p->n) {
        struct E *pe = &ae[1 - i];
        if (pe->x8 == D_002DFB80)
            func_0017F5B0(p, pe->x8);
    }
}
