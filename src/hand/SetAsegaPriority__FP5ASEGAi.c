/* SetAsegaPriority: give every controller the ASEGA drives the priority n and re-sort its XF's controller list.
 * CTRLASEG layout from the SafeHouse port (asega.cpp: palo, pxf, prio, pnextAsega). */
struct ALO;
struct XF;
struct CTRLASEG {
    /* 0x00 */ int pad0;
    /* 0x04 */ struct ALO *palo;         /* field: SafeHouse port */
    /* 0x08 */ struct XF *pxf;           /* field: SafeHouse port */
    /* 0x0c */ int nPriority;            /* field: SafeHouse port (prio) */
    /* 0x10 */ char pad10[0x28 - 0x10];
    /* 0x28 */ struct CTRLASEG *pnextAsega;  /* field: SafeHouse port */
};
struct ASEGA {
    /* 0x00 */ char pad0[0x34];
    /* 0x34 */ struct CTRLASEG *pctrlFirst;  /* the controllers this ASEGA drives (Lilly's port: pactsegFirst) */
};

void SortXfCtrls(struct ALO *palo, struct XF *pxf) asm("SortXfCtrls__FP3ALOP2XF");

void SetAsegaPriority__FP5ASEGAi(struct ASEGA *pasega, int nPriority)
{
    struct CTRLASEG *pctrl;

    for (pctrl = pasega->pctrlFirst; pctrl; pctrl = pctrl->pnextAsega) {
        pctrl->nPriority = nPriority;
        SortXfCtrls(pctrl->palo, pctrl->pxf);
    }
}
