// 6 diff: $a1/$t0 swap between ret copy and &aref[1] (lui order now fixed by by-value return)
struct CRef {
    int m_tagk; int m_tag;
    CRef(int n, int tagk) { m_tag = n; m_tagk = tagk; }
};
static inline int FEq(CRef &a, CRef &b)
{
    int f;
    if (a.m_tagk != b.m_tagk) {
        f = 0;
    } else {
        switch (a.m_tagk) {
        case 0x15: case 0x17: case 0x18: case 0x19:
        case 0x1F: case 0x20: case 0x21: case 0x22:
            f = a.m_tag == b.m_tag;
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
        case 19: case 20: case 0x24:
            f = 1;
            break;
        default:
            break;
        }
    }
    return f;
}
extern "C" CRef func_00120548(void *pbasic, CRef *aref);
CRef func_00120548(void *pbasic, CRef *aref)
{
    return CRef(FEq(aref[0], aref[1]), 0x17);
}
