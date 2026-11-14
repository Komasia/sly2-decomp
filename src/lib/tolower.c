// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// name: newlib ctype tolower (_ctype_ upper bit -> c + 0x20)
extern unsigned char D_002AA6A1[];
int tolower(int c)
{
    return (D_002AA6A1[c] & 1) ? c + 0x20 : c;
}
