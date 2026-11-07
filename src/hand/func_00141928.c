/* func_00141928: OnRemove (virtual slot 11) of class 55 / class 52 / class 53 (JT) / class 54 (MURRAY), derived
 * from class 52: the SO OnRemove, then the class's own part. Field names are offsets (meaning unknown). */
#include "so.h"

void OnSoRemove__FP2SO(SO *p);
void RetractAsegaPp__FPP5ASEGA(void *);
void func_001EECD0(void *);

typedef struct OBJ {
    /* 0x000 */ SO so;
    /* 0x150 */ char unk_0x150[0x11c];
    /* 0x26c */ char unk_0x26c[0xc90];
    /* 0xefc */ char unk_0xefc[0x18];
    /* 0xf14 */ char unk_0xf14[0x4];
} OBJ;

void func_00141928(OBJ *p)
{
    OnSoRemove__FP2SO(&p->so);
    RetractAsegaPp__FPP5ASEGA(p->unk_0xefc);
    RetractAsegaPp__FPP5ASEGA(p->unk_0xf14);
    func_001EECD0(p->unk_0x26c);
}
