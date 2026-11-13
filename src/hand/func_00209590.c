struct S { int k; void *pv; };
void *func_0020C010(int cb);
void *func_0020CA00(int cb);
void CopyAb(void *dst, void *src, int cb) asm("CopyAb__FPvT0Ui");
void func_00209590(struct S *p)
{
    void *pv;
    switch (p->k) {
    case 2:
        pv = func_0020C010(0x40);
        CopyAb(pv, p->pv, 0x40);
        p->pv = pv;
        break;
    case 3:
        pv = func_0020CA00(0xD0);
        CopyAb(pv, p->pv, 0xD0);
        p->pv = pv;
        break;
    }
}
