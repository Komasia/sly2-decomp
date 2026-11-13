typedef struct CRef { int m_tagk; int m_tag; } CRef;
typedef struct PAIR { int a; int b; CRef ref; struct PAIR *pnext; } PAIR;
void InitTag(CRef *pref, int tagk) asm("InitTag__4CRef");
void __as__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
CRef *__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
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
                __as__4CRefRC4CRef(&ref, &p->ref);
                break;
            }
        }
    }
    __4CRefRC4CRef(ret, &ref);
    Decref(&ref);
    return ret;
}
