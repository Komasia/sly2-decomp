/* func_0015DA88: the text for the episode menu's chosen movie (the previous one when fPrev): string 0x77 for the odd
 * movies, 0x78 for the even ones. */
#include "h2_epmenu.h"
struct SW { char pad[0x4774]; EPMENU *pepmenu; };
extern struct SW g_sw;
void *func_0013E368(struct SW *psw, int id);   /* a localized string */
void s1_strcpy(void *pchDst, void *pchSrc) asm("strcpy");
void func_0015DA88(void *pchOut, int fPrev)
{
    EPMENU *pepmenu = g_sw.pepmenu;
    int imovie;
    if (!pepmenu)
        return;
    if (fPrev)
        imovie = pepmenu->imovie - 1;
    else
        imovie = pepmenu->imovie;
    switch (imovie) {
    case 1: case 3: case 5: case 7: case 9: case 11: case 13: case 15:
        s1_strcpy(pchOut, func_0013E368(&g_sw, 0x77));
        break;
    case 2: case 4: case 6: case 8: case 10: case 12: case 14: case 16:
        s1_strcpy(pchOut, func_0013E368(&g_sw, 0x78));
        break;
    }
}
