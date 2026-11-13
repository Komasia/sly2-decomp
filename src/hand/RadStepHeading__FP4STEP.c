/* RadStepHeading: the heading of a stepping object: the angle of the x row of its root transform's world matrix. */
#include "so.h"

float atan2f(float y, float x);

// name: SafeHouse port (RadStepHeading)
float RadStepHeading__FP4STEP(SO *pso)
{
    return atan2f(pso->pxfRoot->matWorld.mat[0][1], pso->pxfRoot->matWorld.mat[0][0]);
}
