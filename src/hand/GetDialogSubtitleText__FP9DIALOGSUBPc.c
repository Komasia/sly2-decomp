/* GetDialogSubtitleText: the dialog subtitle line's whole text: the localized string of its id (0x13E368), or empty
 * when no line is up (id -1). Source: SafeHouse port (sound.cpp). */
struct DIALOGSUB {
    /* 0x0 */ int id;   /* field: SafeHouse port (-1 none) */
};
extern char g_sw[];
char *func_0013E368(void *psw, int id);   /* the localized string of an id */
char *strcpy(char *pchDst, const char *pchSrc);

// name: SafeHouse port (GetDialogSubtitleText)
void GetDialogSubtitleText__FP9DIALOGSUBPc(struct DIALOGSUB *pdialogsub, char *pch)
{
    int id = pdialogsub->id;
    if (id == -1) {
        *pch = 0;
        return;
    }
    strcpy(pch, func_0013E368(g_sw, id));
}
