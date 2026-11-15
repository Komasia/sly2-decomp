/* func_001AB7D0 (0x1AB7D0): makes the save directory with its files: the directory (0x1AC748), the index file
 * "/BASCUS-97316YAOTWTD!/BASCUS-97316YAOTWTD!" (5 bytes of "Sly 2"), icon.sys (0x1AC008, title "Sly 2") and the icon
 * (0x1AC260); the first error is returned. */
extern char g_szSaveDirPath[] __asm__("D_002A6BB0");  /* "/BASCUS-97316YAOTWTD!" */
extern char g_szSaveIndex[] __asm__("D_002A6BC8");    /* "/BASCUS-97316YAOTWTD!/BASCUS-97316YAOTWTD!" */
extern char g_szTitle[] __asm__("D_002A6BF8");        /* "Sly 2" */
void *func_001AC748(void *s, char *a);
void *func_001AC900(void *s, char *a, char *b, int n);
void *func_001AC008(void *s, char *a, char *b);
void *load_sly_icon_from_disc(void *s, char *a);
void *func_001AB7D0(void *pmc)
{
    void *nErr = func_001AC748(pmc, g_szSaveDirPath);
    if (nErr)
        return nErr;
    nErr = func_001AC900(pmc, g_szSaveIndex, g_szTitle, 5);
    if (nErr)
        return nErr;
    nErr = func_001AC008(pmc, g_szSaveDirPath, g_szTitle);
    if (nErr)
        return nErr;
    return load_sly_icon_from_disc(pmc, g_szSaveDirPath);
}
