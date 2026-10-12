typedef struct CRef { int m_tagk; int m_tag; } CRef;
void func_00120C48(CRef *ret, void *pbasic, int cref, CRef *aref, int k);
CRef *func_00120CF8(CRef *ret, void *pbasic, int cref, CRef *aref)
{
    func_00120C48(ret, pbasic, cref, aref, 0x24);
    return ret;
}
