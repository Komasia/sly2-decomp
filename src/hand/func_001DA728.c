/* class: HUD widget, the base constructor (its vtable D_002D85E8): no screen object oid (+0x20 -1), then no
 * direction and no message (func_001DA7D0). */
extern char D_002D85E8[];
struct HUDWIDGET {
    /* 0x00 */ int unk_0x0;
    /* 0x04 */ int unk_0x4;
    /* 0x08 */ int unk_0x8;
    /* 0x0c */ void *pvt;
    /* 0x10 */ char pad10[0x10];
    /* 0x20 */ int oidScreen;
};
void func_001DA7D0(struct HUDWIDGET *pwidget);

struct HUDWIDGET *func_001DA728(struct HUDWIDGET *pwidget)
{
    pwidget->unk_0x0 = 0;
    pwidget->unk_0x4 = 0;
    pwidget->pvt = D_002D85E8;
    pwidget->oidScreen = -1;
    func_001DA7D0(pwidget);
    return pwidget;
}
