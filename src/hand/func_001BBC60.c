/* class: the breakables (SafeHouse breakable.cpp: method 0x10CE08 -> 0x1BBC60, an item 1 with an oid, -1 itself). */
struct LO {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int oid;
};
struct ITEM {
    /* 0x0 */ int kind;
    /* 0x4 */ int n;
};
struct ITEM *PitemNew__FP2LOi(struct LO *plo, int kind);

void func_001BBC60(struct LO *plo, int oid)
{
    if (oid == -1) {
        oid = plo->oid;
    }
    PitemNew__FP2LOi(plo, 1)->n = oid;
}
