/* UpdateSoeWorld__FP3SOE (0x1F38A8): UpdateSoPartGeom - when the part's transform moved since the last rebuild, transform
 * its local geometry into world space and queue the owning SO's tree for a bounds update. */
#include "so.h"

void TransformGeom__FP7MATRIX4P4GEOMT1(struct MATRIX4 *pmat, GEOM *pgeomLocal, GEOM *pgeomWorld);
void MarkAloDirty__FP3ALO(SO *pso);

// name: SafeHouse port (UpdateSoeWorld)
void UpdateSoeWorld__FP3SOE(SOPART *ppart)
{
    XF *pxf = ppart->pxf;

    if (ppart->nStampGeom != pxf->nStamp) {
        TransformGeom__FP7MATRIX4P4GEOMT1(&pxf->matWorld, &ppart->geomLocal, &ppart->geomWorld);
        ppart->nStampGeom = ppart->pxf->nStamp;
        MarkAloDirty__FP3ALO(ppart->pso);
    }
}
