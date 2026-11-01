/* func_001BEA40: Init (virtual slot 6) of class 45, derived from class 3 (XFM): the XFM Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);

typedef struct C45 {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x3c];
    /* 0x11c */ float gUnk11c;
    /* 0x120 */ float gUnk120;
    /* 0x124 */ float gUnk124;
} C45;

void func_001BEA40(C45 *p)
{
    InitXfm__FP3XFM(&p->xfm);
    p->gUnk11c = 1.0f;
    p->gUnk120 = 4.0f;
    p->gUnk124 = 1000.0f;
}
