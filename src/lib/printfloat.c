// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 -msoft-float
// SLY2_ASM: gnu-reorder-db
/* printfloat (Sony printf %e/%f support): print a double in scientific form "0.dddddde+N" through the
   _sceSnprintf output function, six digits of mantissa; returns the characters written. Needs -msoft-float. */
typedef int (*PutFunc)(void *, int *, int);
int ftoi(unsigned long);
int _sceSnprintf_pf(PutFunc, void *, int *, const char *, ...);
int printfloat(PutFunc put, void *arg, int *w, double d)
{
    int n = 0;
    int e = 0;
    if (*w == 0) return 0;
    if (d < 0) {
        d = 0 - d;
        n = 1;
        put(arg, w, '-');
        (*w)--;
    }
    if (d < 0.1) {
        while (d < 0.1) {
            d *= 10.0;
            e--;
        }
    } else if (d >= 1.0) {
        while (d >= 1.0) {
            d /= 10.0;
            e++;
        }
    }
    {
        int v = ftoi((unsigned long)(d * 1000000.0));
        n += _sceSnprintf_pf(put, arg, w, "0.%d", v);
    }
    if (e >= 0)
        n += _sceSnprintf_pf(put, arg, w, "e+%d", e);
    else
        n += _sceSnprintf_pf(put, arg, w, "e%d", e);
    return n;
}
