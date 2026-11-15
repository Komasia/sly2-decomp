/* func_001DEDB0: binds the animations of the laser's two end-cap models (PostLoadLaser): for each cap model, its first
 * ASEG child, the ASEGA already running it on the model (else a new one, started paused at speed 1), and the
 * evaluator of the ASEG's scale channel (channel kind 0xC) that sizes the cap when it is drawn. */
#include "h3_laser.h"
#include "cid.h"

typedef struct ASEG { char unk_lo[0x18]; int oid; } ASEG;
typedef struct CHN { int unk_0x0; void *peval; } CHN;   /* animation channel: +4 its evaluator */
typedef struct LASER { char unk_so[0x1A0]; LASERCAP acap[2]; } LASER;
extern struct G g_sw;
void CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct G *psw, int grffso, int cid, void *ploAncestor, int cploMax, ASEG **aplo);
void *func_001F6788(void *palo, int oidAseg);   /* the ASEGA running that ASEG on palo, or 0 */
void *PasegaApplyAseg__Fiiiff(ASEG *paseg, void *palo, int grfapl, float t, float svt);
CHN *PchnFindAseg__FP4ASEGP3ALOPvi(ASEG *paseg, void *palo, int chnk, int fCreate);
void func_001DEDB0(LASER *plaser)
{
    unsigned int icap;
    for (icap = 0; icap < 2; icap++) {
        LASERCAP *pcap = &plaser->acap[icap];
        void *palo = pcap->palo;
        ASEG *paseg;
        CHN *pchn;
        if (palo == 0)
            continue;
        CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 2, CID_ASEG, palo, 1, (ASEG **)&pcap->paseg);
        paseg = pcap->paseg;
        if (paseg == 0)
            continue;
        pcap->pasega = func_001F6788(palo, paseg->oid);
        if (pcap->pasega == 0) {
            pcap->pasega = PasegaApplyAseg__Fiiiff(paseg, palo, 8, 0.0f, 1.0f);
            if (pcap->pasega == 0)
                continue;
        }
        pchn = PchnFindAseg__FP4ASEGP3ALOPvi(paseg, palo, 0xC, 1);
        if (pchn)
            pcap->pevalScale = pchn->peval;
    }
}
