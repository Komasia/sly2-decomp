/* func_001F38A8 (0x1F38A8): UpdateSoPartGeom - when the part's transform moved since the last rebuild, transform
 * its local geometry into world space and queue the owning SO's tree for a bounds update. */
#include "so.h"

void func_001664A0(struct MATRIX4 *pmat, GEOM *pgeomLocal, GEOM *pgeomWorld);
void func_001F4BF8(SO *pso);

void func_001F38A8(SOPART *ppart)
{
    XF *pxf = ppart->pxf;

    if (ppart->nStampGeom != pxf->nStamp) {
        func_001664A0(&pxf->matWorld, &ppart->geomLocal, &ppart->geomWorld);
        ppart->nStampGeom = ppart->pxf->nStamp;
        func_001F4BF8(ppart->pso);
    }
}
