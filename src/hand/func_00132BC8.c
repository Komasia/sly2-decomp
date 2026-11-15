/* EnsureLoSidebagBool (Sly 1 name): the object's sidebag option iopt ensured to a bool value (f != 0). */
struct LO;
struct CRef { int m_tagk; union { int m_n; float m_g; } m_tag; };
void RefEnsureOption(struct CRef *pref, struct LO *pbasic, int iopt, struct CRef *prefValue);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_00132BC8(struct LO *plo, int iopt, int f)
{
    struct CRef ref;
    struct CRef refT;
    ref.m_tagk = 0x17;   /* TAGK_Bool */
    ref.m_tag.m_n = f != 0;
    RefEnsureOption(&refT, plo, iopt, &ref);
    Decref(&refT);
    Decref(&ref);
}
