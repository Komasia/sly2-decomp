/* EnsureLoSidebag* with a 128-bit by-value argument (VECTOR/QW?) passed to func_00129248 (CRef setter/ctor) */
struct LO;
typedef int ti128 __attribute__((mode(TI)));
struct CRef { int m_tagk; union { int m_n; float m_g; } m_tag; };
void RefEnsureOption(struct CRef *pref, struct LO *pbasic, int optid, struct CRef *prefValue);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_00129248(struct CRef *, ti128);
void func_00132DE0(struct LO *plo, int optid, ti128 v)
{
    struct CRef ref;
    struct CRef refT;
    func_00129248(&ref, v);
    RefEnsureOption(&refT, plo, optid, &ref);
    Decref(&refT);
    Decref(&ref);
}
