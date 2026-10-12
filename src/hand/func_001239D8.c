typedef struct CRef { int m_tagk; int m_tag; } CRef;
CRef *func_001239D8(CRef *ret, void *pbasic, CRef *aref)
{
    int r = aref[0].m_tag % aref[1].m_tag;
    ret->m_tagk = 0x15;
    ret->m_tag = r;
    return ret;
}
