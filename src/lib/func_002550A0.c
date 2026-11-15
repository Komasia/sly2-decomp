// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* CPair constructor (called by PpairNew): refcount 0, push onto the live list, and take the current gc mark. */
extern char D_002DD280[];          /* live list of this kind */
extern int D_002DD598;          /* current gc mark value */
typedef struct { int cref; unsigned links : 31; unsigned fMark : 1; } SPLOBJ;
void func_00254F00(SPLOBJ *, void *);   /* push onto a live list */
SPLOBJ *func_002550A0(SPLOBJ *pobj)
{
    pobj->cref = 0;
    func_00254F00(pobj, D_002DD280);
    pobj->fMark = D_002DD598;
    return pobj;
}
