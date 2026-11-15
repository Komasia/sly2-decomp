/* func_0015D9C0: format the current episode's play time (its "dt" progress, in seconds) as hours and minutes for
 * the episode menu. */
#include "h2_epmenu.h"
typedef struct CRef { int m_tagk; float m_g; } CRef;
struct SW { char pad[0x3B58]; SWEPPROGRESS epprogress; char pad2[0x4774 - 0x3BA0]; EPMENU *pepmenu; };
extern struct SW g_sw;
extern char D_003D4A60[];
extern char D_002A5168[];   /* the format */
void NProgress(CRef *pref, void *pvKey, void *pv);
void Decref(CRef *pref) asm("Decref__4CRef");
float fmodf(float a, float b);
void sprintf(char *pch, char *fmt, ...);
void func_0015D9C0(char *pchOut)
{
    struct SW *psw = &g_sw;
    void *pvDt;
    if (psw->pepmenu && (pvDt = psw->epprogress.apvDt[psw->pepmenu->cur]) != 0) {
        CRef ref;
        float dt;
        int cHour, cMinute;
        NProgress(&ref, pvDt, D_003D4A60);
        dt = ref.m_g;
        Decref(&ref);
        cHour = (int)(dt / 3600.0f);
        cMinute = (int)(fmodf(dt, 3600.0f) / 60.0f);
        sprintf(pchOut, D_002A5168, cHour, cMinute);
    }
}
