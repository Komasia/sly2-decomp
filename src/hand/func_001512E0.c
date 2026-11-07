/* Deactivate__10CPACTUATEDP2LOPv: CPHANG virtual slot 2 (leave): stops its ACT1 (DeleteCtrl__FPP4CTRL), runs func_0014D8C0 on the camera,
 * then the CPLCY leave (Deactivate__5CPLCYP2LOPv), passing its two
 * arguments on. */
#include "cm.h"

void DeleteCtrl__FPP4CTRL(void **ppact1);
void func_0014D8C0(CM *pcm);
void Deactivate__5CPLCYP2LOPv(CPLCY *pcplcy, void *pv1, void *pv2);

// name: SafeHouse port (CPACTUATED::Deactivate)
void Deactivate__10CPACTUATEDP2LOPv(CPHANG *pcphang, void *pv1, void *pv2)
{
    DeleteCtrl__FPP4CTRL(&pcphang->pact1);
    func_0014D8C0(&g_cm);
    Deactivate__5CPLCYP2LOPv(&pcphang->cplcy, pv1, pv2);
}
