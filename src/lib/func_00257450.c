// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
/* Refcounted pointer assignment for splice object kind 2 (pool D_004520D0): *ppobj = pobjNew. */
typedef struct { int cref; char pad[8]; int ref; char pad2[4]; void *pobjNext; } S;   /* ref: a CRef */
extern char D_004520D0[];   /* kind-2 slot heap */
void func_00257250(void *, int);
void Decref(void *) asm("Decref__4CRef"); void func_00255438(S *); void func_0011CD98(void *, S *);
void func_00257450(S **ppobj, S *pobjNew)
{
    S *pobj;
    if (pobjNew) pobjNew->cref++;
    pobj = *ppobj;
    if (pobj) {
        if (--pobj->cref == 0) {
            func_00257250(&pobj->pobjNext, 2);
            Decref(&pobj->ref);
            func_00255438(pobj);                     /* unlink from the live list */
            func_0011CD98(D_004520D0, pobj);         /* free the slot */
        }
    }
    *ppobj = pobjNew;
}
