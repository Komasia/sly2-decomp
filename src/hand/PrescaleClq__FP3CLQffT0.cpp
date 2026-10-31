/* PrescaleClq (Sly 1 util.c): pclqDst(u) = pclqSrc(ru * u + du). */
#include "util.h"

void PrescaleClq(CLQ *pclqSrc, float ru, float du, CLQ *pclqDst)
{
    pclqDst->g2 = pclqSrc->g2 * ru * ru;
    pclqDst->g1 = (pclqSrc->g2 + pclqSrc->g2) * ru * du + pclqSrc->g1 * ru;
    pclqDst->g0 = pclqSrc->g2 * du * du + pclqSrc->g1 * du + pclqSrc->g0;
}
