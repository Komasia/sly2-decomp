/* A render target (SafeHouse render.cpp, orig 0x001BE990 / 0x001BE9E8: each owned target, its camera's view /
 * projection (0x1BE6F0 on D_003E1AA0), then the base 0x16E1A8). */
extern char D_003E1AA0[];
void func_001BE6F0(void *p, void *prt);
void func_0016E1A8(void *prt, int n1, int n2);

void func_001BE9E8(void *prt, int n1, int n2)
{
    func_001BE6F0(D_003E1AA0, prt);
    func_0016E1A8(prt, n1, n2);
}
