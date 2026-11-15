/* An object-reference option: the object oid nearest to plo stored in plo's field at +ib. */
struct OPTLO { int oid; int ib; };   /* an object option: the oid, the field's offset */
extern char g_sw[];
int PloFindSwNearest__FP2LO3OIDii(void *, int, int, void *);
void func_0013E590(char *plo, struct OPTLO *popt) {
    *(int *)(plo + popt->ib) = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, popt->oid, plo);
}
