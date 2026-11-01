/* func_001709F8: Init (virtual slot 6) of class 113, derived from class 2 (LO): the LO Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitLo__FP2LO(LO *p);
void func_0011A050(void *, int);

typedef struct C113 {
    /* 0x000 */ LO lo;
    /* 0x050 */ char unk_0x50[0x4];
} C113;

void func_001709F8(C113 *p)
{
    InitLo__FP2LO(&p->lo);
    func_0011A050(p->unk_0x50, 0x18);
}
