typedef struct CRef { int m_tagk; int m_tag; } CRef;
void RefOpObjectOption__FiP4CRefP6CFrame4BIFK(CRef *ret, void *pbasic, int cref, CRef *aref, int k);
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 110 = BIFK SetO, RefOpObjectOption 0x6E)
CRef *RefOpSetO__FiP4CRefP6CFrame(CRef *ret, void *pbasic, int cref, CRef *aref)
{
    RefOpObjectOption__FiP4CRefP6CFrame4BIFK(ret, pbasic, cref, aref, 0x6E);
    return ret;
}
