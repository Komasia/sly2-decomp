/* CRef temporaries (same unsolved pattern as func_001617E0): target recomputes &temp each use, we keep them in s-regs */
class CRef {
public:
    int m_tagk;
    int m_tag;
    CRef(int n) { m_tagk = 0x15; m_tag = n; }
    CRef(const CRef &ref);
    ~CRef() { Decref(); }
    void Decref();
};
class OPT {
public:
    int n0, n4;
    CRef RefSet(CRef ref, void *q);
};
struct S { char pad[0x7C]; int f7c; char pad1[0xA4 - 0x80]; float fa4; char pad2[0xD0 - 0xA8]; OPT od0; OPT od8; OPT oe0; };
extern char D_003D4A60[];
extern "C" void func_00163460(S *p)
{
    if (p->od0.n0) {
        CRef ref(p->f7c);
        p->od0.RefSet(ref, D_003D4A60);
    }
}
