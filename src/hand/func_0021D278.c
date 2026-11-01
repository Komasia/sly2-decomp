/* func_0021D278: Init (virtual slot 6) of class 18, derived from class 3 (XFM): the XFM Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);
void func_001A6CA8(void *, int);

typedef struct C18 {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x8];
    /* 0x0e8 */ int nUnke8;
    /* 0x0ec */ float gUnkec;
    /* 0x0f0 */ char unk_0xf0[0x4];
    /* 0x0f4 */ int nUnkf4;
} C18;

void func_0021D278(C18 *p)
{
    InitXfm__FP3XFM(&p->xfm);
    func_001A6CA8(p, 3);
    p->nUnke8 = 0x17E;
    p->gUnkec = 25.0f;
    p->nUnkf4 = -1;
}
