/* PostLoadLaser__FP2LO: PostLoad (virtual slot 14) of class 85, derived from class 84: the SO PostLoad (func_001F36A8), then the class's
 * own part. */
#include "so.h"

void func_001F36A8(SO *p);
void BindEnd__FP3ALO(void *);
void func_001DEDB0(void *);
void ApplyLaserContacts__FP3ALO(void *, int);

// name: SafeHouse port (PostLoadLaser)
void PostLoadLaser__FP2LO(SO *p)
{
    func_001F36A8(p);
    BindEnd__FP3ALO(p);
    func_001DEDB0(p);
    ApplyLaserContacts__FP3ALO(p, 0);
}
