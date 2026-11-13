/* InitAseg (Sly 1 aseg.c): an animation segment initialized: the LO's init, its list of playing ASEGAs (their
 * links at +0x2C), the speed 1, the suck speed polynomial {1, 0, 0} clamped to [0, 1], and the flag 0x40.
 * Layout: SafeHouse port (sm.h ASEG). */
struct DL { int a[3]; };
struct ASEG {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ unsigned int grfAseg;   /* field: SafeHouse port */
    /* 0x44 */ char pad44[0x50 - 0x44];
    /* 0x50 */ struct DL dlAsega;      /* field: SafeHouse port - its playing ASEGAs */
    /* 0x5c */ char pad5C[0x78 - 0x5c];
    /* 0x78 */ float svt;              /* field: SafeHouse port */
    /* 0x7c */ char pad7C[0x80 - 0x7c];
    /* 0x80 */ float agSuck[3];        /* field: SafeHouse port (gSuck0..2) */
    /* 0x8c */ char pad8C[0x90 - 0x8c];
    /* 0x90 */ float gSuckMin;         /* field: SafeHouse port */
    /* 0x94 */ float gSuckMax;         /* field: SafeHouse port */
};
void InitLo__FP2LO(struct ASEG *paseg);
void InitDl__FP2DLi(struct DL *pdl, int ibDle);

// name: SafeHouse port (InitAseg 0x12F248) + Sly 1 InitAseg
void InitAseg(struct ASEG *paseg) asm("InitAseg__FP4ASEG");
void InitAseg(struct ASEG *paseg)
{
    float *agSuck;
    InitLo__FP2LO(paseg);
    InitDl__FP2DLi(&paseg->dlAsega, 0x2C);
    agSuck = paseg->agSuck;
    paseg->svt = 1.0f;
    paseg->agSuck[0] = 1.0f;
    agSuck[1] = 0;
    agSuck[2] = 0;
    paseg->gSuckMax = 1.0f;
    paseg->gSuckMin = 0;
    paseg->grfAseg |= 0x40;
}
