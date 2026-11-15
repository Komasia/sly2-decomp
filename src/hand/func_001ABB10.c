/* func_001ABB10 (0x1ABB10): a save slot's file name on the card: "/BASCUS-97316YAOTWTD!/save<n>" with n the slot's
 * number (1..3). */
#include "h5_mc.h"
extern char g_szFmtSlotFile[] __asm__("D_002A6C50");  /* "/%s/%s%d" */
extern char g_szSaveDir[] __asm__("D_002A6C60");      /* "BASCUS-97316YAOTWTD!" */
extern char g_szSlotFile[] __asm__("D_002A6C78");     /* "save" */
int sprintf(char *buf, char *fmt, ...);
void func_001ABB10(struct MC *pmc, struct MCSLOT *pslot, char *szName)
{
    sprintf(szName, g_szFmtSlotFile, g_szSaveDir, g_szSlotFile, pslot - pmc->aslot + 1);
}
