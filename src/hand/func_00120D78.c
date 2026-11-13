typedef struct CRef { int m_tagk; int m_tag; } CRef;
typedef struct PAIR { int a; int b; CRef ref; struct PAIR *pnext; } PAIR;
void InitTag(CRef *pref, int tagk) asm("InitTag__4CRef");
void func_00129658(CRef *pref, CRef *prefSrc);
CRef *func_001291A8(CRef *pref, CRef *prefSrc);
void Decref(CRef *pref) asm("Decref__4CRef");
CRef *RefOpNth__FiP4CRefP6CFrame(CRef *ret, void *pbasic, CRef *aref)
{
    CRef ref;
    InitTag(&ref, 0);
    if (aref[0].m_tagk == 0x1F) {
        PAIR *p = (PAIR *)aref[0].m_tag;
        CRef *pn = &aref[1];
        int i;
        for (i = 0; p; p = p->pnext, i++) {
            if (i == pn->m_tag) {
                func_00129658(&ref, &p->ref);
                break;
            }
        }
    }
    func_001291A8(ret, &ref);
    Decref(&ref);
    return ret;
}
