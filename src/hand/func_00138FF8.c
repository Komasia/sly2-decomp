struct N { char pad[0x1088]; void *f1088; void *f108c; };
struct P { char pad[0x160]; int f160; char pad2[0x448 - 0x164]; int f448; };
struct G { char pad[0x4088]; int pool4088; char pad2[0x40a0 - 0x408c]; int pool40a0; };
struct N *func_0011CCC0(void *);
void func_0011CD98(void *, struct N *);
void AppendDlEntry__FP2DLPv(void *, struct N *);
struct N *func_00138FF8(struct G *pg, struct P *p) {
    void *pool = &pg->pool4088;
    struct N *pn = func_0011CCC0(pool);
    if (!pn) return 0;
    if (p->f160 == 2) {
        pn->f1088 = func_0011CCC0(&pg->pool40a0);
        if (!pn->f1088) { func_0011CD98(pool, pn); return 0; }
    }
    pn->f108c = p;
    AppendDlEntry__FP2DLPv(&p->f448, pn);
    return pn;
}
