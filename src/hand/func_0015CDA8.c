typedef struct CRef { int m_tagk; union { int n; float g; } u; } CRef;
#include "h2_epmenu.h"
struct SW { char pad[0x3B58]; SWEPPROGRESS epprogress; };
extern struct SW g_sw;
extern char D_003D4A60[];
extern char g_joy[];
extern int D_002BE26C;      /* everything unlocked */
extern int D_002BE270;      /* the movie the menu returns to (-1: none) */
void NProgress(CRef *pref, void *pvKey, void *pv);
void Decref(CRef *pref) asm("Decref__4CRef");
void func_002123C8(EPMENU *pepmenu);
void SetEpMode__FP6EPMENUii(EPMENU *pepmenu, int mode, int sub);
void ClearJoySteps__FP6JOYPS2(void *pjoy);
static inline float GProgress(void *pvKey)
{
    CRef ref;
    float g;
    NProgress(&ref, pvKey, D_003D4A60);
    g = ref.u.g;
    Decref(&ref);
    return g;
}
static inline int NProgressKey(void *pvKey)
{
    CRef ref;
    int n;
    NProgress(&ref, pvKey, D_003D4A60);
    n = ref.u.n;
    Decref(&ref);
    return n;
}
/* StartEpMenu: start the episode menu: the last open episode is the highest one played, or after one complete
 * (all of them when D_002BE26C); then the start mode on it, or the movie list when coming back from a movie. */
// name: SafeHouse port (StartEpMenu)
void StartEpMenu__FP6EPMENU(EPMENU *pepmenu)
{
    func_002123C8(pepmenu);
    pepmenu->max = 8;
    if (!D_002BE26C) {
        do {
            int nPercent;
            void *pvPercent;
            if (GProgress(g_sw.epprogress.apvDt[pepmenu->max]) != 0.0f)
                break;
            pvPercent = g_sw.epprogress.apvPercent[pepmenu->max - 1];
            nPercent = 0;
            if (pvPercent)
                nPercent = NProgressKey(pvPercent);
            if (nPercent >= 100)
                break;
            pepmenu->max--;
            if (pepmenu->max < 2)
                break;
        } while (!D_002BE26C);
    }
    if (D_002BE270 == -1) {
        pepmenu->cur = pepmenu->max;
        SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Start, -1);
    } else {
        pepmenu->imovie = D_002BE270;
        pepmenu->cur = 0;
        D_002BE270 = -1;
        SetEpMode__FP6EPMENUii(pepmenu, EPMODE_Movies, 0);
    }
    ClearJoySteps__FP6JOYPS2(g_joy);
}
