struct CRef {
    int m_tagk;
    int m_tag;
    CRef() {}
    CRef(bool f) { m_tagk = 0x17; m_tag = f; }
    CRef(const CRef &);
};
extern "C" CRef func_00120960(void *pbasic, CRef *pref);

CRef func_00120960(void *pbasic, CRef *pref)
{
    int tagk = pref->m_tagk;
    return CRef(tagk == 0x1F || tagk == 0);
}
