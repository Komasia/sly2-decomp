struct S { char p0[0x48]; int c; char p1[0x118-0x4C]; int i; };
void func_001DA9E8(struct S *p);
static inline int Clamp(int n, int lo, int hi) {
    if (n < lo) return lo;
    if (n > hi) return hi;
    return n;
}
void func_001DCE90(struct S *p, int i) {
    int c = p->c;
    int n;
    if (c == 0) n = -1;
    else n = Clamp(i, 0, c - 1);
    p->i = n;
    func_001DA9E8(p);
}
