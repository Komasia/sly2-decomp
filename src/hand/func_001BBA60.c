/* class: the breakables (SafeHouse breakable.cpp: setter 1033 -> 0x1BBA60, AddItem(plo, 6, n)): a new item of kind 6
 * with the value at +0x4. */
struct LO;
struct ITEM {
    /* 0x0 */ int kind;
    /* 0x4 */ int n;
};
struct ITEM *PitemNew__FP2LOi(struct LO *plo, int kind);

void func_001BBA60(struct LO *plo, int n)
{
    PitemNew__FP2LOi(plo, 6)->n = n;
}
