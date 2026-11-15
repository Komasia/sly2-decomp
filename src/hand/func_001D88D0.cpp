/* class: progress path: a KEY built from a NULL-terminated list of path strings (func_001D87C0) that lasts: the KEY
 * and its symbols are copied to the world heap (the symbols are built on the stack heap, released with the frame). */
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
struct MSG { int cb; int nKind; };
struct FRAME {
    int a[4];
    FRAME();
    ~FRAME();
};
#include "h3_progress.h"
KEY *PvAllocSwImpl(MSG *pmsg) asm("PvAllocSwImpl__Fi");
void *PvAllocSwCopyImpl(MSG *pmsg, void *pv) asm("PvAllocSwCopyImpl__FiPv");
extern "C" void func_001D87C0(void *pchz, va_list ap, KEY *pkey);
extern "C" KEY *func_001D88D0(void *pchz, ...)
{
    FRAME frame;
    MSG msg;
    MSG *pmsg = &msg;
    va_list ap;
    KEY *pkey;
    va_start(ap, pchz);
    pmsg->cb = 8;
    pmsg->nKind = 0x10;
    pkey = PvAllocSwImpl(pmsg);
    func_001D87C0(pchz, ap, pkey);
    {
        void *pvStack = pkey->asym;
        pmsg->cb = pkey->csym * 2;
        pmsg->nKind = 0x10;
        pkey->asym = (unsigned short *)PvAllocSwCopyImpl(pmsg, pvStack);
    }
    return pkey;
}
