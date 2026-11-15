/* CFontBrx::FEnsureLoaded (Sly 1 font.c): make sure the font's bitmap and CLUT are uploaded before drawing with it.
 * When drawing into the main GIFS (D_002DEA00) the upload is sent once per frame (bit ifont of the open frame's
 * mask); for any other GIFS it is always sent. The upload is the font's prebuilt GIFS packets (the bitmap's, then
 * the CLUT's when it has one), each followed by its image data, chained in as DMA refs. Returns whether it was sent (SetupDraw then flushes the texture
 * cache). Field names after Sly 1's CFontBrx; Sly 2 offsets from this code. */
typedef struct QW QW;
typedef struct GIFS GIFS;

typedef struct CFontBrx {
    /* 0x000 */ int ifont;              /* bit number in FRM::grfFontLoaded */
    /* 0x004 */ char unk_0x004[0x54];
    /* 0x058 */ int m_cqwBmpGifs;        /* the bitmap's upload packet (func_0015F710) */
    /* 0x05c */ QW *m_aqwBmpGifs;
    /* 0x060 */ char unk_0x060[0x60];   /* (its static storage) */
    /* 0x0c0 */ int cqwBmpImage;        /* the bitmap's pixels */
    /* 0x0c4 */ QW *aqwBmpImage;
    /* 0x0c8 */ int m_cqwClutGifs;       /* the CLUT's upload packet (0: no CLUT) */
    /* 0x0cc */ QW *m_aqwClutGifs;
    /* 0x0d0 */ char unk_0x0d0[0x60];
    /* 0x130 */ int cqwClutImage;       /* the CLUT's colours */
    /* 0x134 */ QW *aqwClutImage;
} CFontBrx;

typedef struct FRM {
    /* 0x00 */ char unk_0x00[0x2C];
    /* 0x2c */ int grfFontLoaded;
} FRM;

extern FRM *g_pfrmOpen;
extern GIFS D_002DEA00;                  /* the main GIFS */
void EndDmaCnt__4DMAS(GIFS *pgifs);
void AddDmaRefs__4DMASiP2QW(GIFS *pgifs, int cqw, QW *aqw);
void AddDmaCnt__4DMAS(GIFS *pgifs);

int FEnsureLoaded__8CFontBrxP4GIFS(CFontBrx *pfont, GIFS *pgifs)
{
    int fLoad;
    if (pgifs == &D_002DEA00) {
        int grf = 1 << pfont->ifont;
        int grfLoaded = g_pfrmOpen->grfFontLoaded;
        fLoad = (grfLoaded & grf) == 0;
        g_pfrmOpen->grfFontLoaded = grfLoaded | grf;
    } else {
        fLoad = 1;
    }
    if (fLoad) {
        EndDmaCnt__4DMAS(pgifs);
        AddDmaRefs__4DMASiP2QW(pgifs, pfont->m_cqwBmpGifs, pfont->m_aqwBmpGifs);
        AddDmaRefs__4DMASiP2QW(pgifs, pfont->cqwBmpImage, pfont->aqwBmpImage);
        if (pfont->m_cqwClutGifs) {
            AddDmaRefs__4DMASiP2QW(pgifs, pfont->m_cqwClutGifs, pfont->m_aqwClutGifs);
            AddDmaRefs__4DMASiP2QW(pgifs, pfont->cqwClutImage, pfont->aqwClutImage);
        }
        AddDmaCnt__4DMAS(pgifs);
    }
    return fLoad;
}
