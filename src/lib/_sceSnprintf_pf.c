// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
int _sceSnprintf(void *a, void *b, int n, const char *fmt, va_list ap);
/* _sceSnprintf_pf (libkernel): varargs front end of _sceSnprintf that keeps a running count of the space
   left in *pleft. */
int _sceSnprintf_pf(void *out, void *outarg, int *pleft, const char *fmt, ...)
{
    va_list ap;
    int written;

    va_start(ap, fmt);
    written = _sceSnprintf(out, outarg, *pleft, fmt, ap);
    *pleft -= written;
    return written;
}
