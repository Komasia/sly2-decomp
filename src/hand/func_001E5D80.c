/* func_001E5D80: Init (virtual slot 6) of class 10, derived from class 3 (XFM): the XFM Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);

typedef struct C10 {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x68];
    /* 0x148 */ int nUnk148;
    /* 0x14c */ char unk_0x14c[0x2c];
    /* 0x178 */ int nUnk178;
} C10;

void func_001E5D80(C10 *p)
{
    InitXfm__FP3XFM(&p->xfm);
    p->nUnk148 = -1;
    p->nUnk178 = 1;
}
