/* EnsureLoSidebagBool (Sly 1 name); C++ original inlined CRef ctor/Set*, ~CRef -> Decref (Decref) */
struct LO;
struct CRef { int m_tagk; union { int m_n; float m_g; } m_tag; };
void RefEnsureOption(struct CRef *pref, struct LO *pbasic, int optid, struct CRef *prefValue);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_00132BC8(struct LO *plo, int optid, int v)
{
    struct CRef ref;
    struct CRef refT;
    ref.m_tagk = 0x17;
    ref.m_tag.m_n = v != 0;
    RefEnsureOption(&refT, plo, optid, &ref);
    Decref(&refT);
    Decref(&ref);
}
