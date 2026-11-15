struct S { char pad[0x17C]; int n; };
void func_002311B0(struct S *p);
void PropeEnsure__FP2LOi(struct S *p, int n);
// name: vt slot 41 = Clone (CloneLo / CloneEmitter / CloneVolbtn in the same slot) of PATH (cid 0x0A)
void ClonePath__FP4PATHT0(struct S *p)
{
    func_002311B0(p);
    if (p->n) {
        p->n = 0;
        PropeEnsure__FP2LOi(p, 0);
    }
}
