extern "C" {void*func_001291A8(void*,const void*);void Decref(void*) asm("Decref__4CRef");}
class CRef {
public:
    int m_tagk;
    int m_tag;
    CRef(int n) { m_tagk = 0x15; m_tag = n; }
    CRef(const CRef &ref) { func_001291A8(this,&ref); }
    ~CRef() { Decref(this); }

};
struct OPT;
extern char D_003D4A60[];
extern "C" CRef func_00258200(OPT *, const CRef &, void *);   /* set a progress value */
static inline void SetPv(OPT *pv,const CRef&r,void*){CRef arg(r);const CRef&ret=func_00258200(pv,arg,D_003D4A60);}
struct SW { char pad[0x3B20]; OPT *poptCoins; };   /* the progress "loot ccoin" (SafeHouse screenrt.cpp) */
extern SW g_sw;
extern "C" void ShowCoinCounter(SW *psw) asm("ShowCoinCounter__FP2SW");
/* func_001617E0: set the coin count in the progress and show the coin counter. */
extern "C" void func_001617E0(void *pv, int ccoin)
{
    SW *psw = &g_sw;
    {
        OPT *popt = psw->poptCoins;
        CRef ref(ccoin);
        SetPv(popt, ref, D_003D4A60);
    }
    ShowCoinCounter(psw);
}
