// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Reset the CPair pool: empty its live list and free every slot of its heap. */
extern int D_002DD280, D_002DD284, D_002DD288, D_002DD28C;   /* live list: head, pages in use, ... */
extern char D_004520A8[];                                  /* CPair slot heap */
void func_0011CDB8(void *);                                 /* free all slots */
void func_00257E88(void)
{
    D_002DD280 = 0;
    D_002DD288 = 0;
    D_002DD28C = 0;
    D_002DD284 = 0;
    func_0011CDB8(D_004520A8);
}
