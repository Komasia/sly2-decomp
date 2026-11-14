/* class: HUD widget (HUD widget vtable entries: 9 focus change, 10 Show 0x1D98B0, 11 Hide 0x1D9910, 12 find the screen object
 * 0x1DA770, 13 reset 0x1DA7B0, 14 the state): the base Hide (entry 11) - the widget taken out of the HUD's list D_003D9E70, then the
 * focus brought up to date (0x1D95B8). */
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct HUDLIST {
    /* 0x0 */ DL dl;
    /* 0xc */ void *pwidgetFocus;
} HUDLIST;

extern HUDLIST D_003D9E70;   /* the HUD's widgets (SafeHouse hudwidget.h) */
int FFindDlEntry__FP2DLPv(DL *pdl, void *pv);
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
void func_001D95B8(HUDLIST *plist);

void func_001D9910(void *pwidget)
{
    if (FFindDlEntry__FP2DLPv(&D_003D9E70.dl, pwidget)) {
        RemoveDlEntry__FP2DLPv(&D_003D9E70.dl, pwidget);
        func_001D95B8(&D_003D9E70);
    }
}
