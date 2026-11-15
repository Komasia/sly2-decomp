/* DemoteAsegaOnAlo: DemoteAsegaOnXf on each of palo's records (0x100 bytes each, ALO +0x50 / +0x54) whose (tag +0x9C,
 * kind +0x94) matches one of the cpair pairs (-1: any). Layout: SafeHouse port (asega.h, lo.h XF). */
struct PAIR { int tag; int kind; };
struct XF { char pad[0x94]; int kind; int f98; int tag; char pad2[0x100 - 0xa0]; };   /* field: SafeHouse port */
struct ALO { char pad[0x50]; int cxf; struct XF *axf; };
void DemoteAsegaOnXf__FiiP2XF(void *pasega, struct ALO *palo, struct XF *pxf);
// name: SafeHouse port (DemoteAsegaOnAlo)
void DemoteAsegaOnAlo__FP5ASEGAP3ALOiPv(void *pasega, struct ALO *palo, int cpair, struct PAIR *apair)
{
    int ixf, ipair;
    for (ixf = 0; ixf < palo->cxf; ixf++) {
        struct XF *pxf = &palo->axf[ixf];
        for (ipair = 0; ipair < cpair; ipair++) {
            struct PAIR *ppair = &apair[ipair];
            if ((pxf->tag == ppair->tag || ppair->tag == -1) && (pxf->kind == ppair->kind || ppair->kind == -1)) {
                DemoteAsegaOnXf__FiiP2XF(pasega, palo, pxf);
                break;
            }
        }
    }
}
