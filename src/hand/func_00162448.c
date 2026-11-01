/* func_00162448: Init (virtual slot 6) of class 132, derived from class 2 (LO): the LO Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitLo__FP2LO(LO *p);
void func_0011A050(void *, int);

typedef struct C132 {
    /* 0x000 */ LO lo;
    /* 0x050 */ char unk_0x50[0x1c];
    /* 0x06c */ int nUnk6c;
    /* 0x070 */ int nUnk70;
    /* 0x074 */ char unk_0x74[0xc];
    /* 0x080 */ char unk_0x80[0x1c];
    /* 0x09c */ float gUnk9c;
    /* 0x0a0 */ float gUnka0;
    /* 0x0a4 */ char unk_0xa4[0x8];
    /* 0x0ac */ int nUnkac;
    /* 0x0b0 */ int nUnkb0;
    /* 0x0b4 */ int nUnkb4;
} C132;

void func_00162448(C132 *p)
{
    InitLo__FP2LO(&p->lo);
    p->gUnk9c = 480.0f;
    p->gUnka0 = 720.0f;
    p->nUnk6c = -1;
    p->nUnk70 = -1;
    p->nUnkac = -1;
    p->nUnkb0 = -1;
    p->nUnkb4 = -1;
    func_0011A050(p->unk_0x80, 0x84);
}
