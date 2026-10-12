typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
CRef *func_00129518(CRef *pref, int n)
{
    Decref__4CRef(pref);
    pref->m_tag = n;
    pref->m_tagk = 0x15;
    return pref;
}
