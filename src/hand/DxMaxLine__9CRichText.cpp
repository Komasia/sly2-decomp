class CFontBrx {
public:
    float DxFromCh(char ch);
};
class CRichText {
public:
    char *m_achz;
    char *m_pchCur;
    CFontBrx *m_pfontCur;
    void Reset();
    char ChNext();
    float DxMaxLine();
};
static inline float GMax(float a, float b) { return a > b ? a : b; }
float CRichText::DxMaxLine()
{
    float dxMax = 0.0f;
    float dx = dxMax;
    char ch;
    Reset();
    while ((ch = ChNext()) != 0) {
        if (ch == '\n') {
            dxMax = GMax(dxMax, dx);
            dx = 0.0f;
        } else {
            dx += m_pfontCur->DxFromCh(ch);
        }
    }
    dxMax = GMax(dxMax, dx);
    return dxMax;
}
