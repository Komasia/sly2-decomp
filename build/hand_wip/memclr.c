// SLY2_CC: tools/compilers/ee-gcc2.96
// SLY2_CFLAGS: -O2 -G0 -fno-delayed-branch
void memclr(char *p, int n)
{
    while (n--) *p++ = 0;
}
