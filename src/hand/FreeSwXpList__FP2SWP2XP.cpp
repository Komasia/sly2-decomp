/* FreeSwXpList (0x1A7E10): returns a list of contacts (linked by XP +0xAC) to the world's contact slot heap
 * (SW +0x3D40). */
struct SLOTHEAP { int a[4]; };
struct XP { char pad[0xAC]; XP *pxpNextSw; };
struct SW { char pad[0x3D40]; SLOTHEAP slotheapXp; };
void FreeSlotheapPv(SLOTHEAP *psh, void *pv) __asm__("func_0011CD98");
void FreeSwXpList(SW *psw, XP *pxp)
{
    while (pxp) {
        XP *pxpNext = pxp->pxpNextSw;
        FreeSlotheapPv(&psw->slotheapXp, pxp);
        pxp = pxpNext;
    }
}
