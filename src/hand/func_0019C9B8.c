/* func_0019C9B8: Init (virtual slot 6) of class 40, derived from class 3 (XFM): the XFM Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);

typedef struct C40 {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x8];
    /* 0x0e8 */ float gUnke8;
} C40;

void func_0019C9B8(C40 *p)
{
    InitXfm__FP3XFM(&p->xfm);
    p->gUnke8 = 100.0f;
}
