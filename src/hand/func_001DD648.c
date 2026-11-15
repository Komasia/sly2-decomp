/* class: the timed message HUD widget D_003DA4F0: its constructor - the base HUD widget, its vtable D_002D83E8, its screen object
 * 0x52D, then no direction / message (func_001DA7D0). */
extern char D_002D83E8[];
struct HUDWIDGET {
    /* 0x00 */ int a, b, c;
    /* 0x0c */ void *pvt;
    /* 0x10 */ char pad10[0x10];
    /* 0x20 */ int oidScreen;
};
struct HUDWIDGET *func_001DA728(struct HUDWIDGET *pwidget);   /* the base constructor */
void func_001DA7D0(struct HUDWIDGET *pwidget);

struct HUDWIDGET *func_001DD648(struct HUDWIDGET *pwidget)
{
    func_001DA728(pwidget);
    pwidget->pvt = D_002D83E8;
    pwidget->oidScreen = 0x52D;
    func_001DA7D0(pwidget);
    return pwidget;
}
