/* CFont::PopScaling (Sly 1 font.c): restore the scale saved by the matching PushScaling. Field names from Sly 1's
 * CFont; the Sly 2 offsets come from this code (Sly 2 keeps the scale before the scale stack). */
typedef struct SFR {
    float rxScale;
    float ryScale;
} SFR;

typedef struct CFont {
    /* 0x00 */ char unk_0x00[0x10];
    /* 0x10 */ float m_rxScale;
    /* 0x14 */ float m_ryScale;
    /* 0x18 */ int m_csfr;        /* entries in use in m_asfr */
    /* 0x1c */ SFR m_asfr[4];
} CFont;

void PopScaling__5CFont(CFont *pfont)
{
    SFR *psfr;
    pfont->m_csfr--;
    psfr = &pfont->m_asfr[pfont->m_csfr];
    pfont->m_rxScale = psfr->rxScale;
    pfont->m_ryScale = psfr->ryScale;
}
