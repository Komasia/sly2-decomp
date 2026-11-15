// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Reset the kind-2 pool: empty its live list and free every slot of its heap. */
extern int D_002DD290, D_002DD294, D_002DD298, D_002DD29C;   /* live list: head, pages in use, ... */
extern char D_004520D0[];                                  /* kind-2 slot heap */
void func_0011CDB8(void *);                                 /* free all slots */
void func_00257F08(void)
{
    D_002DD290 = 0;
    D_002DD298 = 0;
    D_002DD29C = 0;
    D_002DD294 = 0;
    func_0011CDB8(D_004520D0);
}
