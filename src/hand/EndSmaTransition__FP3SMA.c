/* EndSmaTransition: a state machine player's transition ends: no transition animation any more, the state it led to
 * becomes the current one, and the change is announced. Layout: SafeHouse port (smrun.h SMA). */
struct ASEGA;
struct SMA {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ struct ASEGA *pasega;   /* field: SafeHouse port - the transition playing */
    /* 0x34 */ int ismsCur;            /* field: SafeHouse port */
    /* 0x38 */ int ismsNext;           /* field: SafeHouse port - the state the transition leads to */
};
void NotifySmaState(struct SMA *psma, int ismsOld, int ismsNew) asm("NotifySmaState__FP3SMAii");

// name: SafeHouse port (EndSmaTransition)
void EndSmaTransition__FP3SMA(struct SMA *psma)
{
    int ismsNext, ismsCur;
    psma->pasega = 0;
    ismsNext = psma->ismsNext;
    ismsCur = psma->ismsCur;
    psma->ismsNext = -1;
    psma->ismsCur = ismsNext;
    NotifySmaState(psma, ismsCur, ismsNext);
}
