/* func_00183900: Init (virtual slot 6) of class 88, derived from class 48 (SO): the SO Init, then the class's own
 * part. Field names are offsets (meaning unknown). */
#include "so.h"

void InitSo__FP2SO(SO *p);
void func_00182C70(void *);
void func_001F7918(void *, int, int);

typedef struct C88 {
    /* 0x000 */ SO so;
    /* 0x150 */ char unk_0x150[0x8];
    /* 0x158 */ float gUnk158;
    /* 0x15c */ char unk_0x15c[0x20];
    /* 0x17c */ int nUnk17c;
    /* 0x180 */ char unk_0x180[0xc];
    /* 0x18c */ int nUnk18c;
} C88;

void func_00183900(C88 *p)
{
    InitSo__FP2SO(&p->so);
    func_00182C70(p->unk_0x150);
    p->nUnk17c = 0;
    p->gUnk158 = 300.0f;
    p->nUnk18c = 1;
    func_001F7918(p, 0x03FFFFFF, 8);
    func_001F7918(p, 0x03188001, 0);
}
