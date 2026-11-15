/* A new controller of the given kind (0x12E238 picks the class) for the record pxf of palo, with its priority and
 * the record mode it sets while it is the head; not yet added to the record (the PctrlNew* callers add it).
 * Layout: SafeHouse port (xf.h CTRL). */
typedef struct CTRL {
    /* 0x00 */ int kind;    /* field: SafeHouse port */
    /* 0x04 */ int palo;    /* field: SafeHouse port */
    /* 0x08 */ int pxf;     /* field: SafeHouse port */
    /* 0x0c */ int prio;    /* field: SafeHouse port */
    /* 0x10 */ int pnext;   /* field: SafeHouse port */
    /* 0x14 */ int mode;    /* field: SafeHouse port */
} CTRL;
CTRL *func_0012E238(void *kind);   /* a new controller of the kind (sets kind) */
CTRL *func_0012DB50(void *kind, int palo, int pxf, int prio, int mode)
{
    CTRL *pctrl = func_0012E238(kind);
    pctrl->palo = palo;
    pctrl->pxf = pxf;
    pctrl->prio = prio;
    pctrl->mode = mode;
    return pctrl;
}
