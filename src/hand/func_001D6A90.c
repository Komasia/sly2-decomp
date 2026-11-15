/* class: launcher, class 0x70 (SafeHouse launcher.cpp: InitLo 0x1D6A90, vt slot 7): an object that throws another one
 * at a target. Initialise it: the LO init, then the throw curves - lead time 0,0,0 clamped to [0, FLT_MAX],
 * distance 0,1,0 clamped to [0, FLT_MAX], pitch 0.5. */
extern float D_002A7874;      /* FLT_MAX */
struct VECTOR3 { float x, y, z; };
struct LAUNCHER {             /* field: SafeHouse port (launcher.cpp LAUNCHER) */
    /* 0x00 */ char pad0[0x70];
    /* 0x70 */ struct VECTOR3 polyPredict;    /* lead time a + d (b + d c) by the distance d */
    /* 0x7c */ int pad7C;
    /* 0x80 */ int gPredictMin;               /* its clamp (min stored as integer 0) */
    /* 0x84 */ float gPredictMax;
    /* 0x88 */ char pad88[8];
    /* 0x90 */ struct VECTOR3 polyDisplace;   /* the throw's distance by d */
    /* 0x9c */ int pad9C;
    /* 0xa0 */ int gDisplaceMin;
    /* 0xa4 */ float gDisplaceMax;
    /* 0xa8 */ char padA8[8];                 /* rangeAngular: the spin's speed */
    /* 0xb0 */ float gPitch;                  /* the ballistic case's pitch (VecBallisticVelocity) */
};
void InitLo__FP2LO(struct LAUNCHER *plauncher);
static inline void SetVector(struct VECTOR3 *pv, float x, float y, float z) { pv->x = x; pv->y = y; pv->z = z; }

void func_001D6A90(struct LAUNCHER *plauncher)
{
    InitLo__FP2LO(plauncher);
    SetVector(&plauncher->polyPredict, 0, 0, 0);
    plauncher->gPredictMin = 0;
    plauncher->gPredictMax = D_002A7874;
    SetVector(&plauncher->polyDisplace, 0, 1.0f, 0);
    plauncher->gPitch = 0.5f;
    plauncher->gDisplaceMax = D_002A7874;
    plauncher->gDisplaceMin = 0;
}
