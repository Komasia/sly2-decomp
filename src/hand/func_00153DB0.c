/* UpdateDetectorObject__FP2LOf: Update (virtual slot 15) of class 16, derived from class 3 (XFM): the LO Update (func_001A5E28), then the class's
 * own part. */
#include "so.h"

void func_001A5E28(LO *p, float dt);
void UpdateDetector__FP8DETECTOR(void *);

// name: SafeHouse port (UpdateDetectorObject)
void UpdateDetectorObject__FP2LOf(LO *p, float dt)
{
    func_001A5E28(p, dt);
    UpdateDetector__FP8DETECTOR(p);
}
