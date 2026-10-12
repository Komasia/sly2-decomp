typedef struct CRef { int m_tagk; int m_tag; } CRef;
CRef *func_001208A0(CRef *ret, void *pbasic, CRef *pref)
{
    int tagk = pref->m_tagk;
    ret->m_tagk = 0x17;
    ret->m_tag = tagk == 0x18;
    return ret;
}
