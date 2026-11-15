/* func_001ADDF0 (0x1ADDF0): a HUD widget's constructor: the base 0x1DA728, screen object 0x5D4 (+0x20), then
 * 0x1DA7D0 (no state). */
extern "C" void func_001DA7D0(void *p);
struct CBase {
    int a, b, c;
    CBase() __asm__("func_001DA728");
    virtual void f();
};
struct CDer : CBase {
    int x10, x14, x18, x1c, x20;
    CDer() __asm__("func_001ADDF0");
    virtual void f();
};
CDer::CDer()
{
    x20 = 0x5D4;
    func_001DA7D0(this);
}
