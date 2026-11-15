#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(void *pv);
    CRef &operator=(qword q);
    CRef &operator=(bool f);
    CRef &operator=(int n);
    CRef &operator=(float g);
};
extern "C" CRef RefSetArgsFromSplice(int c, void *aref, int *ak, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
struct LO { char pad[0xC]; VTENT *pvt; };
extern "C" { CRef func_00104E80(LO *p, int c, void *aref); }
CRef func_00104E80(LO *p, int c, void *aref)
{
    int ak[2] = {0x2030, 2};
    union { qword q; } u;
    int n;
    CRef ref = RefSetArgsFromSplice(2, aref, ak, &n, &u);
    ref.Decref();
    ref.InitTag(0x24);
    VTENT *pvte = &p->pvt[78];
    ((void (*)(void *, int, void *))pvte->pfn)(VT_THIS(p, pvte), n, &u);
    return ref;
}
