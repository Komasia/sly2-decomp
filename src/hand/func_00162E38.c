struct G { char pad[0x3B18]; int f3b18; char pad2[0x3C84 - 0x3B1C]; int f3c84; };
extern struct G g_sw;
int func_0020E040(struct G *p);
int func_00210B70(void);
void RequestTransition__FP2SWPUc3OIDT2iT2(struct G *p, int n, int a, int b, int c, int d);
void func_00162E38(int n)
{
    struct G *pg = &g_sw;
    pg->f3b18 = n;
    if (!func_0020E040(pg) && !pg->f3c84)
        RequestTransition__FP2SWPUc3OIDT2iT2(pg, func_00210B70(), 0x189, -1, 0, -1);
}
