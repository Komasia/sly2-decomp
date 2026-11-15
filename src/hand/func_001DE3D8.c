/* func_001DE3D8: adds an object id to the laser's overlap object list (Splice setter 448; at most 7). */
#include "h3_laser.h"
typedef struct LASER { char unk_so[0x150]; unsigned int coid; int aoid[COID_LASER_MAX]; } LASER;
void func_001DE3D8(LASER *plaser, int oid)
{
    if (plaser->coid < COID_LASER_MAX) {
        plaser->aoid[plaser->coid++] = oid;
    }
}
