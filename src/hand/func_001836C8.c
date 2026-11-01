/* func_001836C8: Init (virtual slot 6) of class 38, derived from class 3 (XFM): the XFM Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);
void func_00182C70(void *);

typedef struct C38 {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x4];
} C38;

void func_001836C8(C38 *p)
{
    InitXfm__FP3XFM(&p->xfm);
    func_00182C70(p->unk_0xe0);
}
