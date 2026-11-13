extern "C" {void*func_001291A8(void*,const void*);void Decref(void*) asm("Decref__4CRef");}
class CRef {
public:
    int m_tagk;
    int m_tag;
    CRef(int n) { m_tagk = 0x15; m_tag = n; }
    CRef(const CRef &ref) { func_001291A8(this,&ref); }
    ~CRef() { Decref(this); }

};
struct O;
extern char D_003D4A60[];
extern "C" CRef func_00258200(O *, const CRef &, void *);
static inline void SetPv(O *pv,const CRef&r,void*){CRef arg(r);const CRef&ret=func_00258200(pv,arg,D_003D4A60);}
struct G { char pad[0x3B20]; O *f3b20; };
extern G g_sw;
extern "C" void ShowCoinCounter(G *pg) asm("ShowCoinCounter__FP2SW");
extern "C" void func_001617E0(void *pv, int n)
{
    G *pg = &g_sw;
    {
        O *po = pg->f3b20;
        CRef ref(n);
        SetPv(po, ref, D_003D4A60);
    }
    ShowCoinCounter(pg);
}
