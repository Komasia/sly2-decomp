typedef struct CRef { int m_tagk; int m_tag; } CRef;
void Decref__4CRef(CRef *pref);
// name: SafeHouse port (CRef::SetPair)
CRef *SetPair__4CRefP5CPair(CRef *pref, int *p)
{
    (*p)++;
    Decref__4CRef(pref);
    pref->m_tag = (int)p;
    pref->m_tagk = 0x1F;
    return pref;
}
