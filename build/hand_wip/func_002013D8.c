/* early-return path's func_0012A0B0 call is not cross-jumped in target; mine merges it -> 47 diffs */
typedef struct { int tagk; int tag; } CRef;
struct E { int pad[2]; int x8; int pad2; struct E *pNext; };
struct L { int c; struct E *pFirst; };
void func_0012A0B0(CRef *pr, int tagk);
void func_00201360(CRef *pr, int a, int *px, int *ptag, int *pdst);
void func_00129658(CRef *pd, CRef *ps);
void func_00129EC8(CRef *pr);
CRef *func_002013D8(CRef *pret, struct L *pl, int tag, int unused, int *pc, int *adst)
{
    struct E *pe;
    if (pl->c == 0) {
        *pc = 0;
        func_0012A0B0(pret, 0x24);
        return pret;
    }
    *pc = 0;
    for (pe = pl->pFirst; pe; pe = pe->pNext) {
        CRef r;
        CRef t;
        r.tagk = -1;
        func_00201360(&t, 1, &pe->x8, &tag, &adst[*pc]);
        func_00129658(&r, &t);
        func_00129EC8(&t);
        (*pc)++;
        func_00129EC8(&r);
    }
    func_0012A0B0(pret, 0x24);
    return pret;
}
