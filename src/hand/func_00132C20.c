/* EnsureLoSidebagInt (Sly 1 name): the object's sidebag option iopt ensured to an integer value. */
struct LO;
struct CRef { int m_tagk; union { int m_n; float m_g; } m_tag; };
void RefEnsureOption(struct CRef *pref, struct LO *pbasic, int iopt, struct CRef *prefValue);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_00132C20(struct LO *plo, int iopt, int n)
{
    struct CRef ref;
    struct CRef refT;
    ref.m_tagk = 0x15;   /* TAGK_S32 */
    ref.m_tag.m_n = n;
    RefEnsureOption(&refT, plo, iopt, &ref);
    Decref(&refT);
    Decref(&ref);
}
