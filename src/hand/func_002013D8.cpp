struct CRef;
extern "C" {
void InitTag(CRef *pr, int tagk) asm("InitTag__4CRef");
void func_001291A8(CRef *pr, const CRef *ps);
CRef *func_00129658(CRef *pd, const CRef *ps);
void Decref(CRef *pr) asm("Decref__4CRef");
}
struct CRef {
    int tagk;
    int tag;
    CRef() { tagk = -1; }
    CRef(int k) { InitTag(this, k); }
    CRef(const CRef &r) { func_001291A8(this, &r); }
    CRef &operator=(const CRef &r) { func_00129658(this, &r); return *this; }
    ~CRef() { Decref(this); }
};
struct E { int pad[2]; CRef ref8; E *next; };
struct L { int count; E *first; };
extern "C" CRef RefSetArgsFromSplice(int count, CRef *values, int *tags, ...)
    __asm__("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" CRef func_002013D8(L *list, int tag, int unused, int *count, int *dest)
{
    if (list->count == 0) {
        *count = 0;
        return CRef(0x24);
    }
    *count = 0;
    for (E *e = list->first; e; e = e->next) {
        CRef r;
        r = RefSetArgsFromSplice(1, &e->ref8, &tag, &dest[*count]);
        ++*count;
    }
    return CRef(0x24);
}
