struct O;
struct L { struct O *po; };
struct O { char pad[0x14]; struct L *p14; char pad2[0x1E8]; struct O *p200; };
int func_00132B10(struct O *p, int n);
struct O *func_00174898(struct O *p) {
    if (!p) return 0;
    if (func_00132B10(p->p14->po, 0x38)) return p->p14->po;
    if (func_00132B10(p, 0x4F) && func_00132B10(p->p200->p14->po, 0x38)) return p->p200->p14->po;
    return 0;
}
