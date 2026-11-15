// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* kernel patch helper: first word in [p, end) equal to `val`, or 0. */
int *kFindAddress(int *p, int *end, int val)
{
    for (; *p != val && p < end; p++) ; if (p >= end) return 0; return p;
}
