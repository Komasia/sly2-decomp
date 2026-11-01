/* func_00183F08: Init (virtual slot 6) of class 35, derived from class 3 (XFM): the XFM Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);
void func_00182C70(void *);

typedef struct C35 {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x10];
    /* 0x0f0 */ int nUnkf0;
    /* 0x0f4 */ char unk_0xf4[0x8];
    /* 0x0fc */ int nUnkfc;
    /* 0x100 */ char unk_0x100[0x10];
    /* 0x110 */ float gUnk110;
} C35;

void func_00183F08(C35 *p)
{
    InitXfm__FP3XFM(&p->xfm);
    func_00182C70(p->unk_0xe0);
    p->nUnkf0 = 1;
    p->gUnk110 = 200.0f;
    p->nUnkfc = 0;
}
