// PasegaFindAseg: the ASEGA of paseg playing on palo (its list of playing ASEGAs, linked at +0x2C), or null.
// Layout: SafeHouse port (asega.h ASEGA palo +0x18, sm.h ASEG apasega +0x50). The DLI is the unused list iterator.
struct ALO;
struct ASEGA { char pad[0x18]; ALO *palo; char pad2[0x10]; ASEGA *pasegaNext; };
struct ASEG { char pad[0x50]; ASEGA *pasegaFirst; };
struct DLI { void *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
ASEGA *PasegaFindAseg(ASEG *paseg, ALO *palo)
{
    DLI dli;
    ASEGA *p;
    for (p = paseg->pasegaFirst; p; p = p->pasegaNext)
        if (p->palo == palo) return p;
    return 0;
}
