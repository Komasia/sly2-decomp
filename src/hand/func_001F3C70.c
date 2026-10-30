/* RenderSoSelf (0x1F3C70): SO virtual slot 18. Draws the SO's glob set at its current alpha when the SO is
 * visible in the current render pass (LO::grfvis & D_002DDF54). */
#include "so.h"

void func_001F3C10(SO *pso);
void func_00168638(void *pglobset, void *pv, SOBOUNDS *psobounds, float uAlpha, float uAlphaSort);
extern int D_002DDF54;   /* visibility mask of the current pass */

void RenderSoSelf__FP2SOP2CMP2RO(SO *pso)
{
    float uAlpha;

    if (pso->lo.grfvis & D_002DDF54) {
        func_001F3C10(pso);
        uAlpha = pso->uAlpha;
        func_00168638(pso->globset, 0, pso->psobounds, uAlpha, uAlpha);
    }
}
