/* func_001512E0: CPHANG virtual slot 2 (leave): stops its ACT1 (func_0012E460), runs func_0014D8C0 on the camera,
 * then the CPLCY leave (func_0014FCE8), passing its two
 * arguments on. */
#include "cm.h"

void func_0012E460(void **ppact1);
void func_0014D8C0(CM *pcm);
void func_0014FCE8(CPLCY *pcplcy, void *pv1, void *pv2);

void func_001512E0(CPHANG *pcphang, void *pv1, void *pv2)
{
    func_0012E460(&pcphang->pact1);
    func_0014D8C0(&D_002DDF40);
    func_0014FCE8(&pcphang->cplcy, pv1, pv2);
}
