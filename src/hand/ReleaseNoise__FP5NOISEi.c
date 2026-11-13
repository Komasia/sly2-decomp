/* ReleaseNoise: drop a reference to an AI noise; the last one frees it as ReleaseAsega frees an ASEGA: its two DL
 * links are unlinked (func_00256EE0 / func_002580A8), func_001334A8, and it goes back to the noises' slot heap
 * (D_003E1498). */
struct NOISE {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ int cref;
};
struct SLOTHEAP;
extern struct SLOTHEAP D_003E1498;   /* the noises' slot heap */
void func_00256EE0(void *pv, int n);
void func_002580A8(void *pv, int n);
void func_001334A8(void *pv);
void func_0011CD98(struct SLOTHEAP *pslotheap, void *pv);

// name: SafeHouse port (ReleaseNoise)
void ReleaseNoise__FP5NOISEi(struct NOISE *pnoise, int n)
{
    int cref = pnoise->cref - 1;
    pnoise->cref = cref;
    if (cref <= 0) {
        func_00256EE0(pnoise, 0);
        func_002580A8((char *)pnoise + 4, 0);
        func_001334A8(pnoise);
        func_0011CD98(&D_003E1498, pnoise);
    }
}
