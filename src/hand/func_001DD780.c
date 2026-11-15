/* class: a HUD dialog widget: is its screen object fully open (+0x58 and +0x64 both state 2)? */
struct O { char pad[0x58]; int n58; char p1[8]; int n64; };   /* the screen object */
struct HUDWIDGET { char pad[0x24]; struct O *pscreen; };

int func_001DD780(struct HUDWIDGET *pwidget)
{
    struct O *pscreen = pwidget->pscreen;
    if (!pscreen)
        return 0;
    if (pscreen->n58 != 2)
        return 0;
    return pscreen->n64 == 2;
}
