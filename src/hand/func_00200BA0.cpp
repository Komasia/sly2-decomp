class CRef;
extern "C" void Decref(CRef *pref) asm("Decref__4CRef");
class CRef {
public:
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &ref) asm("__4CRefRC4CRef");
    ~CRef() { Decref(this); }
};
class CSidebag { public: int FFindBinding(int sym, CRef *pref); };
struct S { int a; CSidebag *psidebag; };
extern "C" int PeopidFind(S *p, int n) asm("PeopidFind__FP5BASICi");
CRef RefGetPeopid(S *p, int n) asm("RefGetPeopid__FP5BASICP5EOPID");
CRef RefGetOption(S *p, int n) asm("RefGetOption__FP5BASICi");
CRef RefGetOption(S *p, int n)
{
    if (n <= 0x4D0) {
        return RefGetPeopid(p, PeopidFind(p, n));
    }
    CRef ref;
    p->psidebag->FFindBinding(n, &ref);
    return ref;
}
