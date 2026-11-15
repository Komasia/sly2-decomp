// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Reset the CFrame pool: empty its live list and free every slot of its heap. */
extern int D_002DD2A0, D_002DD2A4, D_002DD2A8, D_002DD2AC;   /* live list: head, pages in use, ... */
extern char D_004520F8[];                                  /* CFrame slot heap */
void func_0011CDB8(void *);                                 /* free all slots */
void func_00257EC8(void)
{
    D_002DD2A0 = 0;
    D_002DD2A8 = 0;
    D_002DD2AC = 0;
    D_002DD2A4 = 0;
    func_0011CDB8(D_004520F8);
}
