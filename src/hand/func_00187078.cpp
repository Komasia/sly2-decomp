/* AddGrfusr (Sly 1 joy.c). */
#include "joy.h"

void AddGrfusr(int mask)
{
    g_grfusr |= mask;
    UpdateGrfjoytFromGrfusr();
}
