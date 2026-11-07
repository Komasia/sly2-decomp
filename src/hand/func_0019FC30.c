#include "vec.h"
typedef int qword __attribute__((mode(TI)));
struct S4C { char pad[0x148]; long fl; };
struct A { char pad[0x40]; int x40; char pad2[0x4C-0x44]; struct S4C *x4c; char pad3[0x60-0x50]; qword x60; char pad4[0x88-0x70]; float x88; };
struct B { char pad[0x10C]; int x10c; };
struct P { char pad[0x208]; struct A *x208; char pad2[0x108C-0x20C]; int x108c; char pad3[0x18C4-0x1090]; struct B *x18c4; int x18c8; };
extern struct VECTOR D_002A2DD0;
void RecordSafeGround__FP5ACTORP3SOEG9VU_VECTOR(void *p, int a, qword q);
void RecordSafeTarget__FP5ACTORP2LOf(void *p, void *b, float g);
void UpdateSafeInteract__FP5ACTOR(void *p);
void UpdateSafePipe__FP5ACTOR(void *p);
// name: SafeHouse port (UpdateSafeGround)
void UpdateSafeGround__FP5ACTOR(struct P *p)
{
    struct VECTOR v = D_002A2DD0;
    switch (p->x18c8) {
    case 0: case 1: case 5: case 6: case 9: case 10: case 11: case 12:
    case 15: case 16: case 17: case 20: case 23: case 24:
    {
        struct A *pa = p->x208;
        if (pa && pa->x88 > 0.7f && !(pa->x4c->fl & 0x20000000) && !p->x108c)
            RecordSafeGround__FP5ACTORP3SOEG9VU_VECTOR((char *)p + 0x9E0, pa->x40, pa->x60);
        break;
    }
    case 3: case 22:
    {
        struct B *pb = p->x18c4;
        if (!pb->x10c)
            RecordSafeTarget__FP5ACTORP2LOf((char *)p + 0x9E0, pb ? (char *)pb + 0x100 : 0, 0.0f);
        break;
    }
    case 7:
        UpdateSafeInteract__FP5ACTOR((char *)p + 0x4C0);
        break;
    case 8:
        UpdateSafePipe__FP5ACTOR((char *)p + 0xF50);
        break;
    }
}
