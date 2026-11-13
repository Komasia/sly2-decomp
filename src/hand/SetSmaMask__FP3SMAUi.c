/* SetSmaMask: the transitions a playing state machine may take; a transition now playing that the new mask disallows
 * is finished and another one chosen. Layout: SafeHouse port (smrun.h SMA, sm.h SMT). */
struct ASEGA;
struct SMT {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ unsigned int value;     /* field: SafeHouse port - the mask bits of the transition */
};
struct SMA {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ struct ASEGA *pasega;   /* field: SafeHouse port - the transition playing */
    /* 0x34 */ char pad34[0x40 - 0x34];
    /* 0x40 */ struct SMT *psmt;       /* field: SafeHouse port */
    /* 0x44 */ char pad44[0x48 - 0x44];
    /* 0x48 */ unsigned int grfMask;   /* field: SafeHouse port - the transitions allowed */
};
void FinishSmaTransition__FP3SMA(struct SMA *psma);
void ChooseSmaTransition__FP3SMAi(struct SMA *psma, int fForce);

// name: SafeHouse port (SetSmaMask)
void SetSmaMask__FP3SMAUi(struct SMA *psma, unsigned int grf)
{
    psma->grfMask = grf;
    if (psma->pasega != 0 && (psma->psmt->value & grf)) {
        FinishSmaTransition__FP3SMA(psma);
        ChooseSmaTransition__FP3SMAi(psma, 0);
    }
}
