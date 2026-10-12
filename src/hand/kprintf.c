typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
int vprintf(char *fmt, va_list ap);
int kprintf(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    return vprintf(fmt, ap);
}
