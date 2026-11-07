struct S { char p0[8]; void *p8; };
extern char g_sw[];
void func_001A2BD0(void *p);
void RequestTransition__FP2SWPUc3OIDT2iT2(void *g, int a, int b, int c, int d, int e);
void func_001DD8E0(struct S *p) {
    func_001A2BD0(p->p8);
    RequestTransition__FP2SWPUc3OIDT2iT2(g_sw, 0, 0x189, -1, 1, -1);
}
