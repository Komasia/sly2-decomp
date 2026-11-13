/* AddRefNoise: one more reference to an AI noise (released by ReleaseNoise). NOISE is a reference-counted BASIC
 * like ASEGA: the count is at +0x10. */
struct NOISE {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ int cref;
};

// name: SafeHouse port (AddRefNoise)
void AddRefNoise__FP5NOISE(struct NOISE *pnoise)
{
    pnoise->cref++;
}
