// SLY2_CC: tools/compilers/ee-gcc2.96
// SLY2_CFLAGS: -O2 -G0
/* libmpeg (sceMpegCreate): initialise a ring-buffer descriptor {base, size, read, write} over `size` bytes at `base`. */
void func_0024B8F8(int *ring, int base, int size)
{
    ring[0] = base;     /* start */
    ring[1] = size;
    ring[2] = base;     /* read position */
    ring[3] = base;     /* write position */
}
