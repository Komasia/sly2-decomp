// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Reset the CSidebag pool: empty its live list and free every slot of its heap. */
extern int D_002DD2C0, D_002DD2C4, D_002DD2C8, D_002DD2CC;   /* live list: head, pages in use, ... */
extern char D_00452148[];                                  /* CSidebag slot heap */
void func_0011CDB8(void *);                                 /* free all slots */
void func_00257F88(void)
{
    D_002DD2C0 = 0;
    D_002DD2C8 = 0;
    D_002DD2CC = 0;
    D_002DD2C4 = 0;
    func_0011CDB8(D_00452148);
}
