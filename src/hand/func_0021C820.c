/* class: a controller kind (a vtable entry at 0x2DB36C): the base copy 0x12CF88 (CTRL fields and the kind's data), then
 * +0x1C from the source's +0xA8. */
typedef struct CTRLC {
    /* 0x00 */ char pad0[0x1c];
    /* 0x1c */ int n1C;
} CTRLC;
typedef struct SRCA8 { char pad0[0xa8]; int nA8; } SRCA8;

void func_0012CF88(CTRLC *pctrl, void *pctrlSrc, int n1, SRCA8 *psrc);

int func_0021C820(CTRLC *pctrl, void *pctrlSrc, int n1, SRCA8 *psrc)
{
    func_0012CF88(pctrl, pctrlSrc, n1, psrc);
    return pctrl->n1C = psrc->nA8;
}
