/* class: progress path: a KEY from a NULL-terminated list of path strings (func_001D87C0), on the stack heap. */
/* EE (single-float EABI) stdarg, from gcc's va-mips.h */
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
#include "h3_progress.h"
struct MSG { int cb; int nKind; };
void *PvAllocStackImpl__Fi(struct MSG *pmsg);
void func_001D87C0(void *pchz, va_list ap, KEY *pkey);

KEY *func_001D89A8(void *pchz, ...)
{
    struct MSG msg;
    va_list ap;
    KEY *pkey;
    va_start(ap, pchz);
    msg.cb = 8;
    msg.nKind = 0x10;
    pkey = PvAllocStackImpl__Fi(&msg);
    func_001D87C0(pchz, ap, pkey);
    return pkey;
}
