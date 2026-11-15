/* FUN_0015e1b0 (0x15FEF8): the height of a rich text wrapped to dxMax: its line count times the base font's line
 * height. */
struct CFont { int pad[3]; int m_dyUnscaled; float m_rxScale; float m_ryScale; };
struct CRichText { int pad[3]; struct CFont *m_pfontBase; };
int ClineWrap__9CRichTextf(struct CRichText *prt, float dxMax);
float FUN_0015e1b0(struct CRichText *prt, float dxMax)
{
    float dyLine = (float)prt->m_pfontBase->m_dyUnscaled * prt->m_pfontBase->m_ryScale;
    return dyLine * (float)ClineWrap__9CRichTextf(prt, dxMax);
}
