struct N { int f0; int pad[2]; int fc; struct N *pnext; int pad2[4]; int f24; };
struct S { char pad[0x90]; struct N *pn; };
void func_002301D0(int, struct S *);
void func_00131B10(int id, int a, struct S *p) {
    struct N *pn = p->pn;
    for (;;) {
        if (!pn) return;
        if (pn->f0 == 0 && pn->f24 == id) { pn->fc = -1; func_002301D0(a, p); return; }
        pn = pn->pnext;
    }
}
