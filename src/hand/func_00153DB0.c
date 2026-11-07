/* UpdateDetectorObject__FP2LOf: Update (virtual slot 15) of class 16, derived from class 3 (XFM): the LO Update (UpdateLo__FP2LO), then the class's
 * own part. */
#include "so.h"

void UpdateLo__FP2LO(LO *p, float dt);
void UpdateDetector__FP8DETECTOR(void *);

// name: SafeHouse port (UpdateDetectorObject)
void UpdateDetectorObject__FP2LOf(LO *p, float dt)
{
    UpdateLo__FP2LO(p, dt);
    UpdateDetector__FP8DETECTOR(p);
}
