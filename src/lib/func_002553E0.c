// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* splice object kind 2 (0x5C bytes) constructor (called by func_00257340): refcount 0, push onto the live list, and take the current gc mark. */
extern char D_002DD290[];          /* live list of this kind */
extern int D_002DD598;          /* current gc mark value */
typedef struct { int cref; unsigned links : 31; unsigned fMark : 1; } SPLOBJ;
void func_00255248(SPLOBJ *, void *);   /* push onto a live list */
SPLOBJ *func_002553E0(SPLOBJ *pobj)
{
    pobj->cref = 0;
    func_00255248(pobj, D_002DD290);
    pobj->fMark = D_002DD598;
    return pobj;
}
