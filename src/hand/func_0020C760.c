struct SW;
extern struct SW g_sw;
struct ALOB { char pad[0x58]; int pxfPos; char p2[0xEC]; unsigned long grfSo; };
struct K2PLAY { char pad[0x34]; struct ALOB *palo; char p2[0x28]; int fBallistic; int p64; char pctrl[4]; };
void DeleteCtrl__FPP4CTRL(void *ppctrl);
void SetXfMode__FP3ALOP2XFi(struct ALOB *palo, int pxf, int mode);
void RecalcSwOxfFilterForObject__FP2SWP2SO(struct SW *psw, struct ALOB *palo);
/* ReleaseK2Ballistic (0x20C760): ends a ballistic flight: its target controller deleted, the object's position
 * record back to mode 2, its SO flag bit 26 cleared and the world's filter recalculated for it. */
// name: SafeHouse port (ReleaseK2Ballistic)
void ReleaseK2Ballistic__FP6K2PLAY(struct K2PLAY *pk2play)
{
    if (pk2play->fBallistic) {
        pk2play->fBallistic = 0;
        if (*(int *)pk2play->pctrl) {
            DeleteCtrl__FPP4CTRL(pk2play->pctrl);
            SetXfMode__FP3ALOP2XFi(pk2play->palo, pk2play->palo->pxfPos, 2);
            pk2play->palo->grfSo &= ~(1L << 26);
            RecalcSwOxfFilterForObject__FP2SWP2SO(&g_sw, pk2play->palo);
        }
    }
}
