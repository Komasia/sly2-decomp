// WIP (Claude agent): 13/32. printf-like: DI; _sceSnprintf(putc_cb, &buf, -1, fmt, ap); EI. -msoft-float + va_start after DI. Left: target frame 0xC0 (0x20 more: unsaved FP vararg area) and prologue saves s0,s1,ra unscheduled before a1..t3.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 -msoft-float
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef char *va_list;
int func_00239450(void);
int func_002394A0(void);
int func_00236878(void *, int);
int func_00235B08(int (*)(void *, int), void *, unsigned int, const char *, va_list);
void func_00236960(const char *fmt, ...)
{
    int buf[4];
    va_list ap;
    int st;
    buf[0] = 0;
    st = func_00239450();
    ap = (char *)__builtin_next_arg(fmt) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    func_00235B08(func_00236878, buf, 0xFFFFFFFF, fmt, ap);
    if (st) func_002394A0();
}
