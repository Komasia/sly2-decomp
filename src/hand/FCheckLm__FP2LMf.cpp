/* FCheckLm (Sly 1 util.c): is g strictly inside the limits? */
#include "util.h"

int FCheckLm(LM *plm, float g)
{
    return (plm->gMin < g) && (g < plm->gMax);
}
