/* CmovieOpen: how many movies the movie list offers: all 0x10 when everything is unlocked (D_002BE26C), else the
 * last open episode's count, less 2 when it was never played, less 1 when it is not complete. */
#include "h2_epmenu.h"
typedef struct CRef { int m_tagk; union { int n; float g; } u; } CRef;
struct SW { char pad[0x3B58]; SWEPPROGRESS epprogress; };
extern struct SW g_sw;
extern char D_003D4A60[];
extern int D_002BE26C;      /* everything unlocked */
extern int D_002BE2D0[];    /* per episode: the movies open */
void NProgress(CRef *pref, void *pvKey, void *pv);
void Decref(CRef *pref) asm("Decref__4CRef");
// name: SafeHouse port (CmovieOpen)
int CmovieOpen__FP6EPMENU(EPMENU *pepmenu)
{
    void *pvDt, *pvPercent;
    int cmovie;
    CRef ref;
    float dt;
    if (D_002BE26C)
        return 0x10;
    cmovie = D_002BE2D0[pepmenu->max];
    pvDt = g_sw.epprogress.apvDt[pepmenu->max];
    pvPercent = g_sw.epprogress.apvPercent[pepmenu->max];
    NProgress(&ref, pvDt, D_003D4A60);
    dt = ref.u.g;
    Decref(&ref);
    if (dt == 0.0f) {
        cmovie -= 2;
    } else {
        int nPercent;
        NProgress(&ref, pvPercent, D_003D4A60);
        nPercent = ref.u.n;
        Decref(&ref);
        if (nPercent <= 99)
            cmovie--;
    }
    return cmovie;
}
