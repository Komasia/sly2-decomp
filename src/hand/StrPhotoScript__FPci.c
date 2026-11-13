/* StrPhotoScript: a text of the current player's photo prompt (actor +0xF38): 0 the subject (0x202730), 1 the
 * feedback (0x2026F8), copied into pch when there is one. Source: SafeHouse port (photo.cpp). */
struct PHOTOPROMPT;
struct ACTOR {
    /* 0x000 */ char pad0[0xf38];
    /* 0xf38 */ struct PHOTOPROMPT *pprompt;
};
extern char g_sw[];
struct ACTOR *PloPlayerPo__FP2SW(void *psw);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
char *func_00202730(struct PHOTOPROMPT *pprompt);
char *func_002026F8(struct PHOTOPROMPT *pprompt);
char *strcpy(char *pchDst, const char *pchSrc);

// name: SafeHouse port (StrPhotoScript)
void StrPhotoScript__FPci(char *pch, int n)
{
    struct ACTOR *pactor = PloPlayerPo__FP2SW(g_sw);
    if (pactor != 0 && FIsBasicDerivedFrom__FP5BASIC3CID(pactor, 0x34)) {
        struct PHOTOPROMPT *pprompt = pactor->pprompt;
        char *pchText = 0;
        if (pprompt != 0) {
            if (n != 0) {
                if (n == 1)
                    pchText = func_002026F8(pprompt);
            } else {
                pchText = func_00202730(pprompt);
            }
        }
        if (pchText != 0)
            strcpy(pch, pchText);
    }
}
