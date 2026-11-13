/* OpenGadgetMenu (the player's Select): the gadget menu of the current character: Sly's (D_002E1E40) 0, Bentley's
 * (D_002DD5BC) 1, Murray's (D_002F7900) 2. Source: SafeHouse port (shop.cpp). */
struct LO;
extern struct LO *D_002E1E40;   /* Sly */
extern struct LO *D_002DD5BC;   /* Bentley */
extern struct LO *D_002F7900;   /* Murray */
extern char g_sw[];
struct LO *PloPlayerPo__FP2SW(void *psw);
void SetGadgetMenu__FPvi(void *pgm, int n);

// name: SafeHouse port (OpenGadgetMenu)
void OpenGadgetMenu__FP2SW(void *pgm)
{
    struct LO *ploPlayer = PloPlayerPo__FP2SW(g_sw);
    if (ploPlayer != 0) {
        if (ploPlayer == D_002E1E40) {
            SetGadgetMenu__FPvi(pgm, 0);
            return;
        }
        if (ploPlayer == D_002DD5BC) {
            SetGadgetMenu__FPvi(pgm, 1);
            return;
        }
        if (ploPlayer == D_002F7900)
            SetGadgetMenu__FPvi(pgm, 2);
    }
}
