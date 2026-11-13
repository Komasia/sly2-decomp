/* class: ALO (SafeHouse physworld.cpp / so.h: option 81, the mass of the object's region entry, made on demand). */
struct ALO;
struct REGENT {
    /* 0x0 */ int pad0;
    /* 0x4 */ float dz;        /* field: SafeHouse port */
    /* 0x8 */ float sRadius;   /* field: SafeHouse port */
    /* 0xc */ float gMass;     /* field: SafeHouse port */
};
struct REGENT *PregentEnsure__FP3ALO(struct ALO *palo);

void func_001F8410(struct ALO *palo, float g)
{
    struct REGENT *pregent = PregentEnsure__FP3ALO(palo);
    if (pregent != 0) {
        pregent->gMass = g;
    }
}
