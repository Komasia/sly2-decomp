/* class: the title HUD widget D_003DA530 (ShowTitle 0x1DD820): its constructor - the base HUD widget, its vtable D_002D8368, its screen object
 * 0x5D2, then no direction / message (func_001DA7D0). */
extern char D_002D8368[];
struct HUDWIDGET {
    /* 0x00 */ int a, b, c;
    /* 0x0c */ void *pvt;
    /* 0x10 */ char pad10[0x10];
    /* 0x20 */ int oidScreen;
};
struct HUDWIDGET *func_001DA728(struct HUDWIDGET *pwidget);   /* the base constructor */
void func_001DA7D0(struct HUDWIDGET *pwidget);

struct HUDWIDGET *func_001DD7D8(struct HUDWIDGET *pwidget)
{
    func_001DA728(pwidget);
    pwidget->pvt = D_002D8368;
    pwidget->oidScreen = 0x5D2;
    func_001DA7D0(pwidget);
    return pwidget;
}
