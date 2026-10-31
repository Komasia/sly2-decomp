/* Sly 1 util.h: limits and quadratic curves. */
#ifndef UTIL_H
#define UTIL_H

/* a range [gMin, gMax] */
typedef struct LM {
    float gMin;
    float gMax;
} LM;

/* quadratic g0 + g1*u + g2*u^2 */
typedef struct CLQ {
    float g0;
    float g1;
    float g2;
    float gUnused;
} CLQ;

extern LM g_lmZeroOne;   /* {0, 1} */

#endif
