struct S { char p0[0x50]; int n50; char p1[0x7C-0x54]; int n7C; };
void StopScptImpl__FP2LO(struct S *p);
void func_001E0290(struct S *p, int n);
void func_001DFFE0(struct S *p) {
    StopScptImpl__FP2LO(p);
    p->n50 = 0;
    func_001E0290(p, -1);
    p->n7C = 1;
}
