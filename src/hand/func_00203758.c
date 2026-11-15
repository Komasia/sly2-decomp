/* func_00203758 (0x203758): whether a photo target is done: its task's FTaskDone, or its own flag without a task. */
#include "h6_photo.h"
int FTaskDone__FP4TASK(PHOTOTASK *ptask);
int func_00203758(PHOTOTARGET *ptarget) { if (ptarget->ptask) return FTaskDone__FP4TASK(ptarget->ptask); return ptarget->fDone; }
