/* class: PROXY (SafeHouse activate.cpp method 1177 -> 0x1CB328): an object acquired unless an instance is attached
 * (0x1CB2E0: the latest attached instance's object). */
struct SW;
int func_001CB2E0(struct SW *pproxy);
void PloAcquireProxyObject__FP2SWi(struct SW *pproxy, int n);

void func_001CB328(struct SW *pproxy)
{
    if (func_001CB2E0(pproxy) == 0) {
        PloAcquireProxyObject__FP2SWi(pproxy, 1);
    }
}
