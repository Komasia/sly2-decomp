// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef char *va_list;
int DIntr(void);
int EIntr(void);
int func_00236878(void *, int);
int _sceSnprintf(int (*)(void *, int), void *, unsigned int, const char *, va_list);
/* libkernel scePrintf: interrupt-safe console printf (formats with _sceSnprintf through the character output
   helper 0x236878, interrupts disabled meanwhile).  The Sony libraries call it for their debug messages and the
   game's own printf ends in it (OSTRM::Flush on fd -1). */
void scePrintf(const char *fmt, ...)
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
