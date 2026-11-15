/* PnProgressSlot (SafeHouse savedata.h, orig 0x1D8C10): the address in g_gamesave of the int / float value at the
 * progress path given as a NULL-terminated list of strings (pchz, ...), e.g. the actors' "hpCur" / "mpCur". The path
 * lives in a stack scope. */
#include "h3_progress.h"
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
typedef struct { int tagk; int tag; } CREF;
typedef struct { int a[4]; } STACKSCOPE;
extern LAYOUT D_003E0EA8;             /* the progress layout */
extern GAMESAVE D_003D4A60;           /* g_gamesave */
void __10STACKSCOPE(STACKSCOPE *pscope);
void _$_10STACKSCOPE(STACKSCOPE *pscope, int n);
void Decref(CREF *pref) asm("Decref__4CRef");
void func_001D87C0(void *pchz, va_list ap, KEY *pkey);
int func_001D7E80(LAYOUT *playout, KEY *pkey, GAMESAVE *pgamesave);

// name: SafeHouse port (PnProgressSlot)
int PnProgressSlot__FPvi(void *pchz, ...)
{
    CREF ref;
    STACKSCOPE scope;
    KEY key;
    va_list ap;
    int pn;
    ref.tagk = -1;
    __10STACKSCOPE(&scope);
    va_start(ap, pchz);
    func_001D87C0(pchz, ap, &key);
    pn = func_001D7E80(&D_003E0EA8, &key, &D_003D4A60);
    _$_10STACKSCOPE(&scope, 2);
    Decref(&ref);
    return pn;
}
