/* class: GAIT (SetGaitMix calls it): its +0x4 object's +0x50. */
typedef struct GAITX { char pad0[0x50]; int n50; } GAITX;
typedef struct GAIT {
    /* 0x0 */ int n0;
    /* 0x4 */ GAITX *px;
} GAIT;

int func_0020BB48(GAIT *pgait)
{
    return pgait->px->n50;
}
