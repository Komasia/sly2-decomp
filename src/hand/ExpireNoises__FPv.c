/* ExpireNoises (the world pass over the noise list): a noise whose template has a lifetime (>= 0) is removed when it
 * is older than that. Layout: SafeHouse port (ainoise.h NOISE). */
struct NOISETMPL {
    /* 0x00 */ char pad0[0x60];
    /* 0x60 */ float tLife;            /* field: SafeHouse port */
};
struct NOISE {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ struct NOISETMPL *ptmpl;   /* field: SafeHouse port */
    /* 0x18 */ char pad18[0x4c - 0x18];
    /* 0x4c */ float t;                /* field: SafeHouse port - when it was made */
};
extern float g_clock;   /* g_clock.t */
void RemoveNoise__FP5NOISE(struct NOISE *pnoise);

// name: SafeHouse port (ExpireNoises)
void ExpireNoises__FPv(struct NOISE *pnoise)
{
    float tLife = pnoise->ptmpl->tLife;
    if (tLife >= 0.0f) {
        if (pnoise->t + tLife < g_clock)
            RemoveNoise__FP5NOISE(pnoise);
    }
}
