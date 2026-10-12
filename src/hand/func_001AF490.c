struct S { char pad[0x24]; int x24; char pad2[0x1C0]; int x1e8; int x1ec; };
void func_001AEAA8(struct S *p, int n);
void func_001AF490(struct S *p)
{
    if (p->x1e8 == 7) {
        func_001AEAA8(p, 3);
        p->x1ec = p->x24 - 1;
    }
}
