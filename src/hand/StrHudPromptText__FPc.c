/* StrHudPromptText (the script string 0x2F1): the HUD prompt's string (the localized string of the prompt's id,
 * D_003DA0D8: the prompt widget D_003DA0C0 +0x18). Source: SafeHouse port (hudwidget.cpp). */
extern int D_003DA0D8;   /* the HUD prompt's string id */
extern char g_sw[];
char *func_0013E368(void *psw, int id);   /* the localized string of an id */
char *strcpy(char *pchDst, const char *pchSrc);

// name: SafeHouse port (StrHudPromptText, hudwidget.cpp)
void StrHudPromptText__FPc(char *pch)
{
    strcpy(pch, func_0013E368(g_sw, D_003DA0D8));
}
