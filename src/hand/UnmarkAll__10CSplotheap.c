/* CSplotheap::UnmarkAll (Sly 1 splotheap.cpp): clear the mark of every allocated splot before a garbage
 * collection pass. Sly 2's splot keeps the mark at +0x10 and the next link at +0x18. */
typedef struct SPLOT {
    /* 0x00 */ char unk_0x00[0x10];
    /* 0x10 */ int fAlive;
    /* 0x14 */ int unk_0x14;
    /* 0x18 */ struct SPLOT *psplotNext;
} SPLOT;

typedef struct CSplotheap {
    /* 0x00 */ SPLOT *m_psplotAlloc;   /* allocated splots */
} CSplotheap;

void UnmarkAll__10CSplotheap(CSplotheap *psplotheap)
{
    SPLOT *psplot = psplotheap->m_psplotAlloc;
    while (psplot) {
        psplot->fAlive = 0;
        psplot = psplot->psplotNext;
    }
}
