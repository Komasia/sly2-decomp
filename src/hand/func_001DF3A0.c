/* UpdateLaser__FP2LOf: Update (virtual slot 15) of the laser (class 0x55, h3_laser.h): the SO Update, then moves the
 * path endpoints (func_001DF3D0). */
#include "so.h"

void UpdateSo__FP2SOf(SO *p, float dt);
void func_001DF3D0(void *);

// name: SafeHouse port (UpdateLaser)
void UpdateLaser__FP2LOf(SO *p, float dt)
{
    UpdateSo__FP2SOf(p, dt);
    func_001DF3D0(p);
}
