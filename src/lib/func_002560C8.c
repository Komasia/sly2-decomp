// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* splice object kind 6 (0x14 bytes) constructor (called by func_00259C18): refcount 0, push onto the live list, and take the current gc mark. */
extern char D_002DD2D0[];          /* live list of this kind */
extern int D_002DD598;          /* current gc mark value */
typedef struct { int cref; unsigned links : 31; unsigned fMark : 1; } SPLOBJ;
void func_00255F38(SPLOBJ *, void *);   /* push onto a live list */
SPLOBJ *func_002560C8(SPLOBJ *pobj)
{
    pobj->cref = 0;
    func_00255F38(pobj, D_002DD2D0);
    pobj->fMark = D_002DD598;
    return pobj;
}
