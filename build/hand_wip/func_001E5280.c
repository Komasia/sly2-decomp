struct VTE { short d; short pad; void (*pfn)(void *, int, int); };
struct O { int pad[3]; struct VTE *vt; };
struct P { char pad[0xA4]; int c; struct O *apo[4]; };
int func_00132B10(void *p, int cid);
void *func_002332B8(void *pdst, void *psrc, int cb);
void func_001E5280(struct P *p, struct O *po, int a, int b)
{
    int i;
    if (!func_00132B10(po, 0x33)) return;
    for (i = 0; i < p->c; i++)
        if (p->apo[i] == po) break;
    if (i >= p->c) return;
    {
        struct O **ppo = &p->apo[i];
        func_002332B8(ppo, ppo + 1, (p->c - i - 1) * 4);
    }
    p->c--;
    po->vt[0x54].pfn((char *)po + po->vt[0x54].d, a, b);
}
