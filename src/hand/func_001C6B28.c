struct VTE { short d; short pad; void (*pf)(); };
struct LO { char pad[0xC]; struct VTE *vt; char pad2[0x150 - 0x10]; int x150; char pad3[0x230 - 0x154]; void *x230; };
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
void RequestTaskState__FP4TASKii(void *p, int n, struct LO *plo);
void func_001C60B8(struct LO *p, int n);
void func_001C6B28(struct LO *p, int n)
{
    if (p->x150 == n) return;
    if (n == 1) {
        SetSource__4CSndPv(PsndNewPlain__Fi(0), 0);
        if (p->x230) RequestTaskState__FP4TASKii(p->x230, 2, p);
        n = 2;
        ((void (*)(void *, int, int, int, int, int))p->vt[3].pf)((char *)p + p->vt[3].d, 5, 0, 0, 0, 0);
    }
    func_001C60B8(p, n);
}
