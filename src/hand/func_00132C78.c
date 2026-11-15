/* EnsureLoSidebagFloat (Sly 1 name): the object's sidebag option iopt ensured to a float value. */
struct LO;
struct CRef { int m_tagk; union { int m_n; float m_g; } m_tag; };
void RefEnsureOption(struct CRef *pref, struct LO *pbasic, int iopt, struct CRef *prefValue);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_00132C78(struct LO *plo, int iopt, float g)
{
    struct CRef ref;
    struct CRef refT;
    ref.m_tagk = 0x16;   /* TAGK_F32 */
    ref.m_tag.m_g = g;
    RefEnsureOption(&refT, plo, iopt, &ref);
    Decref(&refT);
    Decref(&ref);
}
