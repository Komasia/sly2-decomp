// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* Output callback for _sceSnprintf that sends each character to the DECI2 console. */
void deci2Putchar(int);
int func_00236878(void *a, void *b, int c)
{
    if (c) deci2Putchar(c);
    return 1;
}
