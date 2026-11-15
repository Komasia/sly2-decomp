/* func_001DF908: adds a beam to the laser (Splice method, SafeHouse: "0x1DF908 via EOPID455"): each endpoint gets its
 * object id and its authored motion (start fraction, speed, duration, mode: LASERPARAMS). At most 0x40 beams. */
#include "h3_laser.h"
typedef struct LASER { char unk_so[0x198]; int cpair; LASERPAIR *apair; } LASER;
static inline void SetParams(LASERPARAMS *pparams, float fraction, float speed, float duration, int mode) {
    pparams->fraction = fraction;
    pparams->speed = speed;
    pparams->duration = duration;
    pparams->mode = mode;
}
void func_001DF908(LASER *plaser, int oid0, float fraction0, float speed0, float duration0, int mode0,
                   int oid1, float fraction1, float speed1, float duration1, int mode1) {
    if (plaser->cpair < CBEAM_LASER_MAX) {
        LASEREND *pend; LASERPARAMS *pparams;
        pend = &plaser->apair[plaser->cpair].aend[0];
        pend->oid = oid0;
        pparams = &pend->track.params; SetParams(pparams, fraction0, speed0, duration0, mode0);
        pend = &plaser->apair[plaser->cpair].aend[1];
        pend->oid = oid1;
        pparams = &pend->track.params; SetParams(pparams, fraction1, speed1, duration1, mode1);
        plaser->cpair++;
    }
}
