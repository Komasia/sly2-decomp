/* UpdateLaser__FP2LOf: Update (virtual slot 15) of class 85, derived from class 84: the SO Update, then the class's own
 * part. */
#include "so.h"

void UpdateSo__FP2SOf(SO *p, float dt);
void func_001DF3D0(void *);

// name: SafeHouse port (UpdateLaser)
void UpdateLaser__FP2LOf(SO *p, float dt)
{
    UpdateSo__FP2SOf(p, dt);
    func_001DF3D0(p);
}
