// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Reset the CProc pool: empty its live list and free every slot of its heap. */
extern int D_002DD2B0, D_002DD2B4, D_002DD2B8, D_002DD2BC;   /* live list: head, pages in use, ... */
extern char D_00452120[];                                  /* CProc slot heap */
void func_0011CDB8(void *);                                 /* free all slots */
void func_00257F48(void)
{
    D_002DD2B0 = 0;
    D_002DD2B8 = 0;
    D_002DD2BC = 0;
    D_002DD2B4 = 0;
    func_0011CDB8(D_00452120);
}
