/* PostLoadLaser__FP2LO: PostLoad (virtual slot 14) of the laser (class 0x55, h3_laser.h): the SO PostLoad
 * (func_001F36A8), then binds the beam endpoints and the laser's bound box (BindEnd), the end-cap models' animations
 * (func_001DEDB0), and sets the beams' initial lengths (ApplyLaserContacts). */
#include "so.h"

void func_001F36A8(SO *p);
void BindEnd__FP3ALO(void *);
void func_001DEDB0(void *);              /* binds the end-cap models' animations */
void ApplyLaserContacts__FP3ALO(void *, int);

// name: SafeHouse port (PostLoadLaser)
void PostLoadLaser__FP2LO(SO *p)
{
    func_001F36A8(p);
    BindEnd__FP3ALO(p);
    func_001DEDB0(p);
    ApplyLaserContacts__FP3ALO(p, 0);
}
