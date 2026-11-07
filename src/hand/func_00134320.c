struct O { char pad[0x48]; struct O *pnext; };
struct L { char pad[0xec]; struct O *fec; };
struct G { char pad[0x3d10]; struct O *pfirst; };
void MarkAloDirty__FP3ALO(struct L *);
void func_00133A38(struct G *, struct O *, struct O *, int);
void func_00134320(struct G *pg, struct L *pl) {
    struct O *po;
    if (pl->fec) {
        MarkAloDirty__FP3ALO(pl);
        for (po = pg->pfirst; po; po = po->pnext)
            if (po != pl->fec) func_00133A38(pg, pl->fec, po, 0);
    }
}
