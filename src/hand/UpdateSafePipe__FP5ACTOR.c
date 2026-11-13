/* UpdateSafePipe: on a pipe that is not unsafe (its +0x19C) the actor records it as its safe place (its part at
 * +0x190) at its distance along it. Layout: SafeHouse port (damage.cpp: the pipe sub-object, actor +0xF50). */
struct LO;
struct ACTOR;
struct PIPE {
    /* 0x000 */ char pad0[0x190];
    /* 0x190 */ char abPart[0xc];
    /* 0x19c */ int fUnsafe;
};
struct ACTPIPE {
    /* 0x00 */ struct ACTOR *pactor;
    /* 0x04 */ char pad4[0xc - 0x4];
    /* 0x0c */ struct PIPE *ppipe;   /* field: SafeHouse port (ploF5C) */
    /* 0x10 */ float s;              /* field: SafeHouse port (sCrvF50) */
};
void RecordSafeTarget(void *psafe, void *ppart, struct PIPE *ppipe, float s) asm("RecordSafeTarget__FP5ACTORP2LOf");

// name: SafeHouse port (UpdateSafePipe)
void UpdateSafePipe__FP5ACTOR(struct ACTPIPE *pap)
{
    struct PIPE *ppipe = pap->ppipe;
    if (!ppipe->fUnsafe)
        RecordSafeTarget((char *)pap->pactor + 0x9e0, ppipe ? ppipe->abPart : 0, ppipe, pap->s);
}
