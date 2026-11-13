/* class: RIP, an emitter particle of kind 4 (SafeHouse emitter.cpp / emitter.h: at its object's world point, +0xF0
 * the object it stays at; the previous point kept at +0x80). */
typedef int qword __attribute__((mode(TI)));
struct LO;
struct RIP {
    /* 0x00 */ char pad0[0x70];
    /* 0x70 */ qword pos;
    /* 0x80 */ qword posPrev;
    /* 0x90 */ char pad90[0xf0 - 0x90];
    /* 0xf0 */ struct LO *ploFollow;   /* field: SafeHouse port */
};
qword PosOfLo__FP2LO(struct LO *plo);

void func_001D0158(struct RIP *prip)
{
    prip->posPrev = prip->pos;
    prip->pos = PosOfLo__FP2LO(prip->ploFollow);
}
