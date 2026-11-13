/* class: the breakables (SafeHouse breakable.cpp: setter 1038 -> 0x1BBB50, AddItem(plo, 11, n)): a new item of kind 11
 * with the value at +0x4. */
struct LO;
struct ITEM {
    /* 0x0 */ int kind;
    /* 0x4 */ int n;
};
struct ITEM *PitemNew__FP2LOi(struct LO *plo, int kind);

void func_001BBB50(struct LO *plo, int n)
{
    PitemNew__FP2LOi(plo, 11)->n = n;
}
