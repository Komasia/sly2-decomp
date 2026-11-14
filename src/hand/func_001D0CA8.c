/* class: a RIP kind (vtable 0x2D7558: its Init, entry 1): the base 0x1CE920 (the arguments passed on), its life 5
 * and the vector +0xA0. */
typedef int qword __attribute__((mode(TI)));
typedef struct RIP {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ float sLife;
    /* 0x1c */ char pad1c[0x84];
    /* 0xa0 */ qword qwA0;
} RIP;
extern qword D_002C1F40;
void func_001CE920(RIP *prip);

void func_001D0CA8(RIP *prip)
{
    func_001CE920(prip);
    prip->sLife = 5.0f;
    prip->qwA0 = D_002C1F40;
}
