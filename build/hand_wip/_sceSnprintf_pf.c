// WIP (Claude agent): -msoft-float removes FP vararg saves; left: frame 0x60 vs 0x80 (target reserves FP area) + s0-before-ra prologue order
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 -msoft-float
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
int _sceSnprintf(void *a, void *b, int n, const char *fmt, va_list ap);
int _sceSnprintf_pf(void *a, void *b, int *pn, const char *fmt, ...)
{
    va_list ap;
    int r;

    va_start(ap, fmt);
    r = _sceSnprintf(a, b, *pn, fmt, ap);
    *pn -= r;
    return r;
}
