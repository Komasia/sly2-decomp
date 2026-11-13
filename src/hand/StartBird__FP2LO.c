/* StartBird (the birds' vt slot 15, the post-load): the ALO's post-load (0x1F36A8), the step segments found, the
 * walk / fly speeds from their clips' root motion (+0x18C -> +0x1CC, +0x1B0 -> +0x1D0), and the bird placed.
 * Source: SafeHouse port (bird.cpp). */
struct ASEG;
struct BIRD {
    /* 0x000 */ char pad0[0x18c];
    /* 0x18c */ struct ASEG *pasegWalk;   /* SafeHouse: segs.apaseg[1] */
    /* 0x190 */ char pad190[0x1b0 - 0x190];
    /* 0x1b0 */ struct ASEG *pasegFly;
    /* 0x1b4 */ char pad1B4[0x1cc - 0x1b4];
    /* 0x1cc */ float svWalk;             /* field: SafeHouse port */
    /* 0x1d0 */ float svFly;
};
void func_001F36A8(struct BIRD *pbird);   /* the ALO's post-load */
void BindStepSegs__FP8STEPSEGS(struct BIRD *pbird);
int FStepLength__FP4ASEGP3ALOPf(struct BIRD *pbird, struct ASEG *paseg, float *psv);
void PlaceBird__FP2LO(struct BIRD *pbird);

// name: SafeHouse port (StartBird)
void StartBird__FP2LO(struct BIRD *pbird)
{
    func_001F36A8(pbird);
    BindStepSegs__FP8STEPSEGS(pbird);
    FStepLength__FP4ASEGP3ALOPf(pbird, pbird->pasegWalk, &pbird->svWalk);
    FStepLength__FP4ASEGP3ALOPf(pbird, pbird->pasegFly, &pbird->svFly);
    PlaceBird__FP2LO(pbird);
}
