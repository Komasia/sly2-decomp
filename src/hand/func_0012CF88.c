/* CTRL copy (vtable slot 6, SafeHouse xf.h "Copy"): pctrl becomes a copy of pctrlSrc for another object / record:
 * kind, priority and mode are copied, palo / pxf are the new ones, and the bytes after +0x1C are copied up to the
 * controller slot size (the slot heap at 0x3E123C, whose cb D_003E1230 + 0xC is). Layout: SafeHouse port (xf.h CTRL). */
typedef struct CTRL {
    /* 0x00 */ int kind;      /* field: SafeHouse port */
    /* 0x04 */ int palo;      /* field: SafeHouse port */
    /* 0x08 */ int pxf;       /* field: SafeHouse port */
    /* 0x0c */ int prio;      /* field: SafeHouse port */
    /* 0x10 */ int pnext;     /* field: SafeHouse port */
    /* 0x14 */ int mode;      /* field: SafeHouse port */
    /* 0x18 */ int pvtbl;
    /* 0x1c */ char ab[1];    /* the kind's own fields */
} CTRL;
typedef struct G { int pad[3]; unsigned int cb; } G;
extern G D_003E1230;          /* +0xC: the controller slot heap 0x3E123C's slot size */
void CopyAb__FPvT0Ui(void *dst, void *src, unsigned int cb);
void func_0012CF88(CTRL *pctrl, CTRL *pctrlSrc, int palo, int pxf)
{
    pctrl->kind = pctrlSrc->kind;
    pctrl->prio = pctrlSrc->prio;
    pctrl->mode = pctrlSrc->mode;
    pctrl->palo = palo;
    pctrl->pxf = pxf;
    CopyAb__FPvT0Ui(pctrl->ab, pctrlSrc->ab, D_003E1230.cb - 0x1C);
}
