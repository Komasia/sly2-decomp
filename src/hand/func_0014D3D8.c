/* __2CM: CM constructor (class 135; also the class factory's, func_00112DA8): BASIC part, CM vtable
 * (D_002CA4D0), then each camera-policy member is constructed; the CPTWOSHOT member at +0x600 is a plain CPLCY
 * with its own vtable (D_002CD378). */
#include "cm.h"

extern VTE D_002CA4D0[];
extern VTE D_002CD378[];
CPLCY *func_0014FCA8(CPLCY *pcplcy);     /* CPLCY */
CPLCY *func_0014FD68(CPLCY *pcplcy);     /* CMPART1 (+0x3A0) */
void *func_00221990(void *pcmpart2);     /* CMPART2 (+0x3B0) */
CPLOOK *func_0014FDE0(CPLOOK *pcplook);  /* CPLOOK (+0x450) */
void *func_0012E760(void *pcpcamera);    /* CPCAMERA (+0x4A8) */
CPLCY *func_00151208(CPLCY *pcplcy);     /* CPHANG (+0x4C0) */
CPLCY *func_00151610(CPLCY *pcplcy);     /* CPCAMBLEND (+0x500) */
CPZOOM *func_00150728(CPZOOM *pcpzoom);  /* CPZOOM (+0x520) */
CPLCY *func_001518C8(CPLCY *pcplcy);     /* CPTURRET (+0x5F0) */

// name: SafeHouse port (CM::CM)
CM *__2CM(CM *pcm)
{
    CPTWOSHOT *pcptwoshot;

    pcm->basic.pframe = NULL;
    pcptwoshot = &pcm->part600;
    pcm->basic.psidebag = NULL;
    pcm->basic.pvt = D_002CA4D0;
    func_0014FD68(&pcm->part3a0);
    func_00221990(pcm->part3b0);
    func_0014FDE0(&pcm->cplook);
    func_0012E760(pcm->part4a8);
    func_00151208(&pcm->part4c0.cplcy);
    func_00151610((CPLCY *)pcm->part500);
    func_00150728(&pcm->cpzoom);
    func_001518C8(&pcm->part5f0);
    func_0014FCA8(&pcptwoshot->cplcy);
    pcptwoshot->cplcy.pvt = D_002CD378;
    return pcm;
}
