/* func_001DE3B0: adds a class id to the laser's overlap class list (Splice setter 449; at most 7). */
#include "h3_laser.h"
typedef struct LASER { char unk_so[0x170]; unsigned int ccid; int acid[COID_LASER_MAX]; } LASER;
void func_001DE3B0(LASER *plaser, int cid)
{
    if (plaser->ccid < COID_LASER_MAX) {
        plaser->acid[plaser->ccid++] = cid;
    }
}
