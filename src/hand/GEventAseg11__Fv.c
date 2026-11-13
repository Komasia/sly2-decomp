/* GEventAseg11: the time of an animation segment's event of kind 11 with id n (PeventLaunch), 0 when there is none.
 * Source: SafeHouse port (sly.cpp). */
struct ASEG;
float *PeventLaunch__FP5KINDEi(struct ASEG *paseg, int n);   /* the event (its time first) */

// name: SafeHouse port (GEventAseg11)
float GEventAseg11__Fv(struct ASEG *paseg, int n)
{
    float *pev = PeventLaunch__FP5KINDEi(paseg, n);
    float t = 0.0f;
    if (pev != 0)
        t = *pev;
    return t;
}
