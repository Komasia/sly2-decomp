/* An ASEG's speed: every ASEGA playing it takes the new ASEG speed (SetAsegaAsegSpeed), then the ASEG's svt (+0x78).
 * Layout: SafeHouse port (sm.h ASEG apasega +0x50, svt +0x78; asega.h ASEGA link +0x2C). */
struct ASEGA { char pad[0x2c]; struct ASEGA *pnext; };
struct ASEG { char pad[0x50]; struct ASEGA *pasegaFirst; char pad2[0x24]; float svt; };
void SetAsegaAsegSpeed__FP5ASEGAf(struct ASEGA *pasega, float svt);
void func_001306F0(struct ASEG *paseg, float svt)
{
    struct { void *a, *b; int c; void *d; } dli;   /* the list iterator (unused) */
    struct ASEGA *pasega;
    for (pasega = paseg->pasegaFirst; pasega; pasega = pasega->pnext)
        SetAsegaAsegSpeed__FP5ASEGAf(pasega, svt);
    paseg->svt = svt;
}
