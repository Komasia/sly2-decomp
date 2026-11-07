struct N { int f0; int pad[2]; int fc; struct N *pnext; int pad2[4]; int f24; };
struct S { char pad[0x90]; struct N *pn; };
void SortXfCtrls__FP3ALOP2XF(int, struct S *);
// name: SafeHouse port (DemoteAsegaOnXf)
void DemoteAsegaOnXf__FiiP2XF(int id, int a, struct S *p) {
    struct N *pn = p->pn;
    for (;;) {
        if (!pn) return;
        if (pn->f0 == 0 && pn->f24 == id) { pn->fc = -1; SortXfCtrls__FP3ALOP2XF(a, p); return; }
        pn = pn->pnext;
    }
}
