// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
/* CPair refcounted pointer assignment: *pppair = ppairNew (add a reference to the new pair, release the old one;
   a pair whose count drops to 0 releases its cdr and car, leaves the live list and goes back to the pool). */
typedef struct { int cref; char pad[4]; int car; char pad2[4]; void *ppairCdr; } S;   /* car: a CRef */
extern char D_004520A8[];   /* CPair slot heap */
void func_00256D40(void *, int);
void Decref(void *) asm("Decref__4CRef"); void func_002550F8(S *); void func_0011CD98(void *, S *);
void func_00256C58(S **pppair, S *ppairNew)
{
    S *ppair;
    if (ppairNew) ppairNew->cref++;
    ppair = *pppair;
    if (ppair) {
        if (--ppair->cref == 0) {
            func_00256D40(&ppair->ppairCdr, 2);
            Decref(&ppair->car);
            func_002550F8(ppair);                    /* unlink from the live list */
            func_0011CD98(D_004520A8, ppair);        /* free the slot */
        }
    }
    *pppair = ppairNew;
}
