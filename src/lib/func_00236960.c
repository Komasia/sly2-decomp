// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef char *va_list;
int DIntr(void);
int EIntr(void);
int func_00236878(void *, int);
int _sceSnprintf(int (*)(void *, int), void *, unsigned int, const char *, va_list);
void func_00236960(const char *fmt, ...)
{
    int buf[4];
    va_list ap;
    int st;
    buf[0] = 0;
    st = DIntr();
    ap = (char *)__builtin_next_arg(fmt) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    _sceSnprintf(func_00236878, buf, 0xFFFFFFFF, fmt, ap);
    if (st) EIntr();
}
