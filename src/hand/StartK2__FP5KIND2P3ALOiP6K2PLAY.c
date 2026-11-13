/* StartK2: a kind-2 move (a leap, KIND2) started on an object: when it has a clip, the player record (0x70 bytes,
 * the guard's +0xDB0) is cleared (twice: the constructor's clear and the assignment's), constructed (0x20C058), given
 * the tuning, the object and the ApplyAseg flags, and set to state 0. Layout: SafeHouse port (guard.h K2PLAY). */
struct ALO;
struct ASEG;
struct KIND2 {
    /* 0x0 */ char pad0[4];
    /* 0x4 */ struct ASEG *paseg;      /* field: SafeHouse port */
};
struct K2PLAY {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ struct KIND2 *ptuning;  /* field: SafeHouse port */
    /* 0x34 */ struct ALO *palo;       /* field: SafeHouse port */
    /* 0x38 */ void *pasega;           /* field: SafeHouse port */
    /* 0x3c */ int grf;                /* field: SafeHouse port */
    /* 0x40 */ char pad40[0x70 - 0x40];
};
void *memset(void *pv, int b, unsigned int cb);
void func_0020C058(struct K2PLAY *pk);   /* the K2PLAY constructor */
void SetK2State__FP6K2PLAYi(struct K2PLAY *pk, int st);

// name: SafeHouse port (StartK2)
void StartK2__FP5KIND2P3ALOiP6K2PLAY(struct KIND2 *ptuning, struct ALO *palo, int grf, struct K2PLAY *pk)
{
    if (ptuning->paseg != 0) {
        memset(pk, 0, sizeof(*pk));
        memset(pk, 0, sizeof(*pk));
        func_0020C058(pk);
        pk->ptuning = ptuning;
        pk->palo = palo;
        pk->grf = grf;
        SetK2State__FP6K2PLAYi(pk, 0);
    }
}
