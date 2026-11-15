// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* CProc constructor (called by PprocNew): refcount 0, push onto the live list, and take the current gc mark. */
extern char D_002DD2B0[];          /* live list of this kind */
extern int D_002DD598;          /* current gc mark value */
typedef struct { int cref; unsigned links : 31; unsigned fMark : 1; } SPLOBJ;
void func_002558C0(SPLOBJ *, void *);   /* push onto a live list */
SPLOBJ *func_00255A58(SPLOBJ *pobj)
{
    pobj->cref = 0;
    func_002558C0(pobj, D_002DD2B0);
    pobj->fMark = D_002DD598;
    return pobj;
}
