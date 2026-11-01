/* func_0017F110: OnRemove (virtual slot 11) of class 76 / class 75 / class 74 / class 71, derived from class 71:
 * the SO OnRemove, then the class's own part. Field names are offsets (meaning unknown). */
#include "so.h"

void OnSoRemove__FP2SO(SO *p);

typedef struct OBJ {
    /* 0x000 */ SO so;
    /* 0x150 */ char unk_0x150[0x3c];
    /* 0x18c */ int nUnk18c;
} OBJ;

void func_0017F110(OBJ *p)
{
    OnSoRemove__FP2SO(&p->so);
    p->nUnk18c = 0;
}
