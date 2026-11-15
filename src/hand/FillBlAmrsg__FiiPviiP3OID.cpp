// FillBlAmrsg: segment table ibAmrsg of each BL entry (stride cbBl): the times of its ASEG's launch events (kind 11) with
// the ids aoid, then each segment's length to the next (wrapping at the ASEG's length +0x74). SafeHouse port (blend.h).
enum OID { OID_Nil };
struct ALO { char pad[0x74]; float tMax; };   // an ASEG: its length
struct BL { int x0; ALO *palo; };
struct MRSG { float t; float dt; };
extern "C" float GEventAseg11(ALO *palo, OID oid) asm("GEventAseg11__Fv");
void FillBlAmrsg(int cbBl, int cbl, void *pbl, int ibAmrsg, int coid, OID *aoid)
{
    int ibl;
    for (ibl = 0; ibl < cbl; ibl++) {
        BL *pblT = (BL *)((char *)pbl + ibl * cbBl);
        ALO *palo = pblT->palo;
        if (palo) {
            MRSG *amrsg = (MRSG *)((char *)pblT + ibAmrsg);
            MRSG *pmrsgPrev;
            MRSG *pmrsg;
            int i;
            pmrsg = amrsg;
            for (i = 0; i < coid; i++, pmrsg++)
                pmrsg->t = GEventAseg11(palo, aoid[i]);
            pmrsg = amrsg;
            pmrsgPrev = &pmrsg[coid - 1];
            for (i = 0; i < coid; i++, pmrsg++) {
                float dt = pmrsg->t - pmrsgPrev->t;
                pmrsgPrev->dt = dt;
                if (dt < 0.0f)
                    pmrsgPrev->dt = dt + palo->tMax;
                pmrsgPrev = pmrsg;
            }
        }
    }
}
