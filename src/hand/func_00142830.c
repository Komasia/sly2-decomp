/* The actor's look target set and held (+0x1100: not chosen each frame). SafeHouse port (actor.h). */
void SetActorLookTarget__FP5ACTORiP2LO(void *pactor, int nKind, int plo);
void func_00142830(char *pactor, int nKind, int plo)
{
    SetActorLookTarget__FP5ACTORiP2LO(pactor, nKind, plo);
    *(int *)(pactor + 0x1100) = 1;   /* fLookHeld */
}
