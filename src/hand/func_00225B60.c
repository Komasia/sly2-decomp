/* UpdateTurret__FP6TURRETf: Update (virtual slot 15) of class 69, derived from class 50 (PO): the SO Update, then the class's
 * own part. */
#include "so.h"

void UpdateSo__FP2SOf(SO *p, float dt);
void UpdateTurretAim__FP6TURRET(void *);
void UpdateTurretZoom__FP3ALO(void *);
void UpdateTurretFire__FP3ALO(void *);

// name: SafeHouse port (UpdateTurret)
void UpdateTurret__FP6TURRETf(SO *p, float dt)
{
    UpdateSo__FP2SOf(p, dt);
    UpdateTurretAim__FP6TURRET(p);
    UpdateTurretZoom__FP3ALO(p);
    UpdateTurretFire__FP3ALO(p);
}
