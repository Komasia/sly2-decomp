/* ShowWorldStats: in a world with stats (0x210AE0) the coin counter, the clue counter when the world has pickups
 * of class 0x5F, a sound (0x32), the time noted (SW +0x4754) and the camera's counter +0x4A4. */
#include "clock.h"
#include "cid.h"
extern char g_sw[];
struct CM { char pad[0x4A4]; int cStatsShown; };
extern struct CM g_cm;
int func_00210AE0(void);
void ShowCoinCounter__FP2SW(void *p);
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *p, int a, int b, int c, int d, int e);
void ShowClueCounter(void *p) asm("ShowClueCounter__FP2SW");
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
// name: SafeHouse port (ShowWorldStats)
void ShowWorldStats__Fv(void)
{
    if (func_00210AE0()) {
        ShowCoinCounter__FP2SW(g_sw);
        if (CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(g_sw, 0x605, CID_PICKUP_5F, 0, 0, 0)) ShowClueCounter(g_sw);
        SetSource__4CSndPv(PsndNewPlain__Fi(0x32), 0);
        *(float *)(g_sw + 0x4754) = g_clock.t;   /* when the stats were shown */
        g_cm.cStatsShown++;
    }
}
