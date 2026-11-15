/* The object's sidebag option iopt ensured to a vector value (passed by value in a quadword; its CRef built by
 * 0x129248). */
struct LO;
typedef int ti128 __attribute__((mode(TI)));
struct CRef { int m_tagk; union { int m_n; float m_g; } m_tag; };
void RefEnsureOption(struct CRef *pref, struct LO *pbasic, int iopt, struct CRef *prefValue);
void Decref(struct CRef *) asm("Decref__4CRef");
void func_00129248(struct CRef *, ti128);
void func_00132DE0(struct LO *plo, int iopt, ti128 vec)
{
    struct CRef ref;
    struct CRef refT;
    func_00129248(&ref, vec);
    RefEnsureOption(&refT, plo, iopt, &ref);
    Decref(&refT);
    Decref(&ref);
}
