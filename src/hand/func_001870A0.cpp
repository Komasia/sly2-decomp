/* RemoveGrfusr (Sly 1 joy.c). */
#include "joy.h"

void RemoveGrfusr(int mask)
{
    g_grfusr &= ~mask;
    UpdateGrfjoytFromGrfusr();
}
