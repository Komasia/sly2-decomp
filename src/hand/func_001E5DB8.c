struct S { char pad[0x17C]; int n; };
void func_002311B0(struct S *p);
void PropeEnsure__FP2LOi(struct S *p, int n);
void func_001E5DB8(struct S *p)
{
    func_002311B0(p);
    if (p->n) {
        p->n = 0;
        PropeEnsure__FP2LOi(p, 0);
    }
}
