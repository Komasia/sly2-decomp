/* func_0020BB48 (0x20BB48): the gait's blend's (+0x4) +0x50 (SetGaitMix reads its scale). */
typedef struct GAITX { char pad0[0x50]; int n50; } GAITX;
typedef struct GAIT {
    /* 0x0 */ void *palo;
    /* 0x4 */ GAITX *pasegbl;
} GAIT;

int func_0020BB48(GAIT *pgait)
{
    return pgait->pasegbl->n50;
}
