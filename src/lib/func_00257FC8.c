// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Reset the kind-6 pool: empty its live list and free every slot of its heap. */
extern int D_002DD2D0, D_002DD2D4, D_002DD2D8, D_002DD2DC;   /* live list: head, pages in use, ... */
extern char D_00452170[];                                  /* kind-6 slot heap */
void func_0011CDB8(void *);                                 /* free all slots */
void func_00257FC8(void)
{
    D_002DD2D0 = 0;
    D_002DD2D8 = 0;
    D_002DD2DC = 0;
    D_002DD2D4 = 0;
    func_0011CDB8(D_00452170);
}
