/* RemoveTargetrecGuard: a guard leaves a target's record: the guards after it moved down one place.
 * Layout: SafeHouse port (aipursuit.h TARGETREC). */
struct GUARD;
struct TARGETREC {
    /* 0x00 */ char pad0[0x28];
    /* 0x28 */ int cpguard;                /* field: SafeHouse port */
    /* 0x2c */ struct GUARD *apguard[1];   /* field: SafeHouse port - the guards pursuing it */
};
int func_0020A658(struct TARGETREC *ptrec, struct GUARD *pguard);   /* the guard's index */
void CopyAb__FPvT0Ui(void *pvDst, void *pvSrc, unsigned int cb);

// name: SafeHouse port (RemoveTargetrecGuard)
void RemoveTargetrecGuard__FP9TARGETREC(struct TARGETREC *ptrec, struct GUARD *pguard)
{
    int i = func_0020A658(ptrec, pguard);
    int c = ptrec->cpguard - 1;
    struct GUARD **ppguard = &ptrec->apguard[i];
    ptrec->cpguard = c;
    CopyAb__FPvT0Ui(ppguard, ppguard + 1, (c - i) * sizeof(struct GUARD *));
}
