void ResetScreenObjPart__FP2LOi(void *p, int k);
void SelectScreenObjPart__FP2LOi(void *p, int k);
// name: SafeHouse port (SelectScreenObjPartHandle)
void SelectScreenObjPartHandle__FP2LOiPi(void *p, int k, int *pk)
{
    if (k == *pk)
        return;
    if (*pk != -1)
        ResetScreenObjPart__FP2LOi(p, *pk);
    *pk = k;
    if (k != -1)
        SelectScreenObjPart__FP2LOi(p, k);
}
