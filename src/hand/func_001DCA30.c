/* class: SHOP (a text callback of the shop's screen object): the text for the shop's message kind (D_003DA180, the
 * shop's +0x30): none 0xDE, question 0xDF, message 0xE0 (localized); empty otherwise. */
extern int D_003DA180;                /* D_003DA150.msg */
extern struct G g_sw;
void *func_0013E368(struct G *psw, int id);   /* a localized text */
void s1_strcpy(char *pchDst, void *pchSrc) asm("strcpy");

void func_001DCA30(char *pch)
{
    int id;
    switch (D_003DA180) {
    case -1: id = 0xDE; break;
    case 0: id = 0xDF; break;
    case 1: id = 0xE0; break;
    default: *pch = 0; return;
    }
    s1_strcpy(pch, func_0013E368(&g_sw, id));
}
