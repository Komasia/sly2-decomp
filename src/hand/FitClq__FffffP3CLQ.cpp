/* FitClq (Sly 1 util.c): the quadratic through (0, g0), (1, g1) and (u, gU). */
#include "util.h"

void FitClq(float g0, float g1, float u, float gU, CLQ *pclq)
{
    pclq->g0 = g0;
    pclq->g2 = ((gU - g0) / u - (g1 - g0)) / (u - 1.0f);
    pclq->g1 = (g1 - g0) - pclq->g2;
}
