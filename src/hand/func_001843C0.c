/* func_001843C0: Init (virtual slot 6) of class 27, derived from class 22: the XFM Init, then the class's own part.
 * Field names are offsets (meaning unknown). */
#include "so.h"

void InitXfm__FP3XFM(XFM *p);
void func_00182C70(void *);

typedef struct C27 {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x50];
    /* 0x130 */ char unk_0x130[0x4];
} C27;

void func_001843C0(C27 *p)
{
    InitXfm__FP3XFM(&p->xfm);
    func_00182C70(p->unk_0x130);
}
