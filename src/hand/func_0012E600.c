/* func_0012E600: Init (virtual slot 6) of class 44, derived from class 3 (XFM): the XFM Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);
extern qword D_002A2DA0;
extern qword g_normalZ;

typedef struct C44 {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x20];
    /* 0x100 */ qword qwUnk100;
    /* 0x110 */ qword qwUnk110;
} C44;

void func_0012E600(C44 *p)
{
    InitXfm__FP3XFM(&p->xfm);
    p->qwUnk100 = D_002A2DA0;
    p->qwUnk110 = g_normalZ;
}
