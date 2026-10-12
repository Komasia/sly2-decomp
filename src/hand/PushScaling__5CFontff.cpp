struct SCL { float rx; float ry; };
class CFont {
public:
    int pad[4];
    float m_rxScale;
    float m_ryScale;
    int m_cscl;
    SCL m_ascl[1];
    void PushScaling(float rx, float ry);
};
void CFont::PushScaling(float rx, float ry)
{
    SCL *pscl = &m_ascl[m_cscl++];
    pscl->rx = m_rxScale;
    pscl->ry = m_rxScale;
    m_rxScale = m_ascl[0].rx * rx;
    m_ryScale = m_ascl[0].ry * ry;
}
