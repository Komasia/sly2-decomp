/* EnsureLoSidebagFloat (Sly 1 name); C++ original inlined CRef ctor/SetF32, ~CRef -> Decref (Decref) */
struct LO;
struct CRef { int m_tagk; union { int m_n; float m_g; } m_tag; };
void RefEnsureOption(struct CRef *pref, struct LO *pbasic, int optid, struct CRef *prefValue);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_00132C78(struct LO *plo, int optid, float g)
{
    struct CRef ref;
    struct CRef refT;
    ref.m_tagk = 0x16;
    ref.m_tag.m_g = g;
    RefEnsureOption(&refT, plo, optid, &ref);
    Decref(&refT);
    Decref(&ref);
}
