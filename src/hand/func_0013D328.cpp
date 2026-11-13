extern "C" { void *func_001291A8(void *, const void *); void Decref(void *) asm("Decref__4CRef"); }
class CRef {
public:
    int m_tagk;
    int m_tag;
    CRef(int tagk, int n) { m_tagk = tagk; m_tag = n; }
    CRef(const CRef &ref) { func_001291A8(this, &ref); }
    ~CRef() { Decref(this); }
};
struct FRAME {
    int a[4];
    FRAME();
    ~FRAME();
};
struct S { char pad[0x194]; void *f194; };
struct O;
extern char D_003D4A60[];
extern "C" {
void SetBootyState(void *, int) asm("SetBootyState__FP2LOi");
O *AkeyStand(S *) asm("AkeyStand__FP2LO");
void AttachStandBooty(S *, int) asm("AttachStandBooty__FP2LO");
CRef func_00258200(O *, const CRef &, void *);
}
static inline void SetPv(O *pv, const CRef &r, void *) { CRef arg(r); const CRef &ret = func_00258200(pv, arg, D_003D4A60); }
// name: SafeHouse port (SetStandBooty)
extern "C" void SetStandBooty__FP2LOi(S *p, int n)
{
    if (p->f194) SetBootyState(p->f194, 0);
    FRAME frame;
    {
        O *po = AkeyStand(p);
        CRef ref(0x15, n);
        SetPv(po, ref, D_003D4A60);
    }
    if (n != -1) AttachStandBooty(p, 0);
}
