/* class: RIP of kind 4, a pickup's glint (SafeHouse emitter.h: 0x1CE888(G, 4, 0) + 0x1D0108: the model at an object's
 * point): the base 0x1CE920, its life 0.5 and two vectors. */
typedef int qword __attribute__((mode(TI)));
struct RIP {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ float sLife;
    /* 0x1c */ int pad1c;
    /* 0x20 */ qword qw20;
    /* 0x30 */ qword qw30;
};
extern qword D_002C1F90;
extern qword D_002C1FA0;
void func_001CE920(struct RIP *prip);

void func_001D0108(struct RIP *prip)
{
    func_001CE920(prip);
    prip->sLife = 0.5f;
    prip->qw30 = D_002C1F90;
    prip->qw20 = D_002C1FA0;
}
