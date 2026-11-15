/* SetProgressPoCurrent (SafeHouse port; SafeHouse savedata.h FSetProgress): write refArg at the progress path given
 * as a NULL-terminated list of strings (fmt, ...) in g_gamesave. */
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
struct CRef {
    int m_tagk;
    int m_tag;
    CRef() { m_tagk = -1; }
    CRef(const CRef &);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
    void Decref();
};
struct FRAME {
    int a[4];
    FRAME();
    ~FRAME();
};
#include "h3_progress.h"
extern GAMESAVE D_003D4A60;                       /* g_gamesave */
extern LAYOUT D_003E0EA8;                         /* the progress layout */
extern "C" void func_001D87C0(const char *pchz, va_list ap, KEY *pkey);
CRef FSetProgress(LAYOUT *playout, KEY *pkey, const CRef &ref, GAMESAVE *pgamesave) asm("FSetProgress__FP4TRIEP4CRefT1Pc");
static inline CRef Eval(KEY *pkey, const CRef &ref, GAMESAVE *pgamesave) { return FSetProgress(&D_003E0EA8, pkey, ref, pgamesave); }
// name: SafeHouse port (SetProgressPoCurrent)
extern "C" CRef SetProgressPoCurrent__FP4CRefPci(const CRef &refArg, const char *fmt, ...)
{
    CRef ref;
    FRAME frame;
    KEY key;
    va_list ap;
    va_start(ap, fmt);
    func_001D87C0(fmt, ap, &key);
    ref = Eval(&key, refArg, &D_003D4A60);
    return ref;
}
