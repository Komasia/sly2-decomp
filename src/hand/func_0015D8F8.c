/* func_0015D8F8: format the current episode's completion percentage for the episode menu: 95% of its progress, plus
 * 5 when its extra flag (D_002BE2F8) is set. */
#include "h2_epmenu.h"
typedef struct CRef { int m_tagk; int m_n; } CRef;
struct SW { char pad[0x3B58]; SWEPPROGRESS epprogress; char pad2[0x4774 - 0x3BA0]; EPMENU *pepmenu; };
extern struct SW g_sw;
extern char D_003D4A60[];
extern void *D_002BE2F8[];
extern char D_002A5160[];   /* the format */
void NProgress(CRef *pref, void *pvKey, void *pv);
void Decref(CRef *pref) asm("Decref__4CRef");
int func_001DAEA8(void *pv);
void sprintf(char *pch, char *fmt, ...);
void func_0015D8F8(char *pchOut)
{
    struct SW *psw = &g_sw;
    void *pvPercent;
    if (psw->pepmenu && (pvPercent = psw->epprogress.apvPercent[psw->pepmenu->cur]) != 0) {
        CRef ref;
        int nPercent;
        NProgress(&ref, pvPercent, D_003D4A60);
        nPercent = ref.m_n;
        Decref(&ref);
        nPercent = nPercent * 95 / 100;
        if (func_001DAEA8(D_002BE2F8[psw->pepmenu->cur]))
            nPercent += 5;
        sprintf(pchOut, D_002A5160, nPercent);
    }
}
