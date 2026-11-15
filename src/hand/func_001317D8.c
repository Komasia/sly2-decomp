/* FWrapAsegaTime: the time back into [0, tMax]: looping (grfapl & 8) wraps it, ping-pong (0x10) reflects it and turns
 * the speed around, otherwise it stops at the end (speed 0). Returns whether the end was passed in the direction of
 * play. Layout: SafeHouse port (asega.h ASEGA). */
struct ASEG { char pad[0x74]; float tMax; };
struct ASEGA { int pad[5]; struct ASEG *paseg; char pad1[0x3C - 0x18]; int grfapl; char pad2[0x44 - 0x40]; float svtLocal; };
float fmodf(float a, float b);
float GModPositive__Fff(float a, float b);
static __inline__ void PingPong(struct ASEGA *pasega, float *pt, float *psvt, float tMax, float tPeriod)
{
    *psvt = __builtin_fabsf(*psvt);
    pasega->svtLocal = __builtin_fabsf(pasega->svtLocal);
    if (tMax <= *pt) {
        *pt = tPeriod - *pt;
        *psvt = -*psvt;
        pasega->svtLocal = -pasega->svtLocal;
    }
}
// name: SafeHouse port (FWrapAsegaTime)
int FWrapAsegaTime__FP5ASEGAPfT1(struct ASEGA *pasega, float *pt, float *psvt)
{
    float tMax = pasega->paseg->tMax;
    float t = *pt;
    int fWrapped = 0;
    if (tMax <= t) {
        if (0.0f < *psvt)
            fWrapped = 1;
        if (pasega->grfapl & 8) {
            *pt = fmodf(t, tMax);
        } else if (pasega->grfapl & 0x10) {
            float tPeriod = tMax + tMax;
            *pt = fmodf(t, tPeriod);
            PingPong(pasega, pt, psvt, tMax, tPeriod);
        } else {
            *pt = tMax;
            *psvt = 0.0f < *psvt ? 0.0f : *psvt;
        }
    } else if (t < 0.0f) {
        if (*psvt < 0.0f)
            fWrapped = 1;
        if (pasega->grfapl & 8) {
            *pt = GModPositive__Fff(t, tMax);
        } else if (pasega->grfapl & 0x10) {
            float tPeriod = tMax + tMax;
            *pt = fmodf(-t, tPeriod);
            PingPong(pasega, pt, psvt, tMax, tPeriod);
        } else {
            *pt = 0.0f;
            *psvt = *psvt < 0.0f ? 0.0f : *psvt;
        }
    }
    return fWrapped;
}
