/* class: the breakables (SafeHouse breakable.cpp: 0x1BBBB0 / 0x1BBC08 / 0x1BBC98 / 0x1BBCF0 - an item 5 in a current
 * event, else at once: func_001F6B48). */
struct LO;
struct ITEM {
    /* 0x0 */ int kind;
    /* 0x4 */ int n;
};
int func_001BBE18(struct LO *pbrk);
struct ITEM *PitemNew__FP2LOi(struct LO *plo, int kind);
void func_001F6B48(struct LO *palo, int n);

void func_001BBCF0(struct LO *plo, int n)
{
    if (func_001BBE18(plo) == 0) {
        func_001F6B48(plo, n);
        return;
    }
    PitemNew__FP2LOi(plo, 5)->n = n;
}
