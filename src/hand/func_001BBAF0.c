/* class: the breakables (the item setters of SafeHouse breakable.cpp, AddItem(plo, k, n)): a new item of kind 9. */
struct LO;
struct ITEM {
    /* 0x0 */ int kind;
    /* 0x4 */ int n;
};
struct ITEM *PitemNew__FP2LOi(struct LO *plo, int kind);

void func_001BBAF0(struct LO *plo, int n)
{
    PitemNew__FP2LOi(plo, 9)->n = n;
}
