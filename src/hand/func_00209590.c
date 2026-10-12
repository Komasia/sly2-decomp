struct S { int k; void *pv; };
void *func_0020C010(int cb);
void *func_0020CA00(int cb);
void func_001AE5A0(void *dst, void *src, int cb);
void func_00209590(struct S *p)
{
    void *pv;
    switch (p->k) {
    case 2:
        pv = func_0020C010(0x40);
        func_001AE5A0(pv, p->pv, 0x40);
        p->pv = pv;
        break;
    case 3:
        pv = func_0020CA00(0xD0);
        func_001AE5A0(pv, p->pv, 0xD0);
        p->pv = pv;
        break;
    }
}
