// CFont::PushScaling (Sly 1 font.c): save the current scale and scale the base scale by (rx, ry).
struct SFR { float rx; float ry; };
class CFont {
public:
    int pad[4];
    float m_rxScale;
    float m_ryScale;
    int m_csfr;
    SFR m_asfr[1];   /* the saved scales; m_asfr[0] is the base scale */
    void PushScaling(float rx, float ry);
};
void CFont::PushScaling(float rx, float ry)
{
    SFR *psfr = &m_asfr[m_csfr++];
    psfr->rx = m_rxScale;
    psfr->ry = m_rxScale;   /* (sic: the game saves rx twice) */
    m_rxScale = m_asfr[0].rx * rx;
    m_ryScale = m_asfr[0].ry * ry;
}
