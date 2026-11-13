/* UpdateRecyclable__3CGc (0x11A800; the name is a Sly 1 shape match): three HUD widget objects (D_003D9E80 the health
 * and gadget power meter of screen object 0x36B, D_003DA0F0, D_003DA150) passed to the empty 0x1D9878, then the two
 * DMA streams D_002DEA00 / D_002DEA28 flushed. */
struct DMAS;
extern char D_003D9E80[];   /* SafeHouse: the HUD meter widget */
extern char D_003DA0F0[];
extern char D_003DA150[];
extern struct DMAS D_002DEA00;
extern struct DMAS D_002DEA28;
void func_001D9878(void *pwidget);   /* empty */
void Flush__4DMAS(struct DMAS *pdmas);

void UpdateRecyclable__3CGc(void)
{
    func_001D9878(D_003D9E80);
    func_001D9878(D_003DA0F0);
    func_001D9878(D_003DA150);
    Flush__4DMAS(&D_002DEA00);
    Flush__4DMAS(&D_002DEA28);
}
