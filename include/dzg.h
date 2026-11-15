/* The contact constraint solver (Sly 1's dzg.c): an LCP over the contacts of a group of SOs, one row (DZ) per
 * constraint, solved by pivoting the rows between the clamped set and their bounds (0x11A550..0x11AE88) with Crout's
 * LU decomposition (CroutDecomp 0x1195E0, CroutSolve 0x1198F8) for the clamped system, and the rows' responses
 * from the SOs (0x1585D8..0x158FBC).
 * Layouts: SafeHouse port (dzg.h); field names follow SafeHouse / Sly 1 style. For C and C++ sources. */
#ifndef DZG_H
#define DZG_H
#include "dl.h"

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

/* DZ::kind */
enum DZK {
    DZK_Contact = 0,    /* bounded below by gMin = 0 */
    DZK_TwoSided = 1    /* friction rows (and kind 11 contacts): clamped from the start (EnforceDzgConstraints) */
};

/* A row (0x28 bytes). */
typedef struct DZ {
    /* 0x00 */ int kind;            /* enum DZK */
    /* 0x04 */ float gMin;
    /* 0x08 */ float gMax;
    /* 0x0C */ float g;             /* the solution */
    /* 0x10 */ float gResidual;     /* the error (the target velocity / depth, then what is left) */
    /* 0x14 */ float dgResidual;    /* its change per unit step of the current pivot */
    /* 0x18 */ float *agCoupling;   /* the couplings with every row (0: not computed yet) */
    /* 0x1C */ struct DZ *pdzPair;  /* the friction row of a contact row and back */
    /* 0x20 */ DLE dle;             /* in one of the DZG's four lists */
} DZ;
#define IB_DZ_DLE 0x20   /* offsetof(DZ, dle): the lists' ibDle */

/* The response entry of a row (0x60 bytes). */
typedef struct DZENT {
    /* 0x00 */ qword dvLin0;        /* the first SO's velocity change per unit */
    /* 0x10 */ qword dvAng0;        /* its angular change */
    /* 0x20 */ qword dvLin1;        /* the second SO's */
    /* 0x30 */ qword dvAng1;
    /* 0x40 */ qword normal;
    /* 0x50 */ struct XP *pxp;      /* the contact */
    /* 0x54 */ qword *aresp;        /* the change of each contact's relative velocity per unit */
    /* 0x58 */ int pad58[2];
} DZENT;

typedef struct DZG {
    /* 0x00 */ int cdzMax;
    /* 0x04 */ int cdz;
    /* 0x08 */ DZ *adz;
    /* 0x0C */ DL dlClamped;        /* rows strictly between their bounds (the solved system) */
    /* 0x18 */ DL dlLower;          /* rows at their lower bound */
    /* 0x24 */ DL dlUpper;          /* rows at their upper bound */
    /* 0x30 */ DL dlOpen;           /* rows not yet considered */
    /* 0x3C */ int cdzClamped;
    /* 0x40 */ float *agA;          /* the clamped rows' coupling matrix (cdzClamped x cdzClamped) */
    /* 0x44 */ float *agLu;         /* its LU decomposition */
    /* 0x48 */ float *agB;          /* the right-hand side */
    /* 0x4C */ float *agX;          /* the solution of the clamped system */
#ifndef DZG_ROWS_ONLY   /* SolveDzgConstraints (0x11AD30) keeps a 0x50-byte DZG of just the rows on its stack */
    /* 0x50 */ int cxp;
    /* 0x54 */ struct XP **apxp;
    /* 0x58 */ int cso;
    /* 0x5C */ struct SO **apso;
    /* 0x60 */ DZENT *aent;
#endif
} DZG;

#endif
