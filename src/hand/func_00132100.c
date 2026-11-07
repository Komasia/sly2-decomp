struct S { char pad[0xe8]; int fe8; };
extern char g_sw[];
void func_001F36A8(struct S *);
void RecalcSwOxfFilterForObject__FP2SWP2SO(void *, struct S *);
void PostBarrierLoad__FP7BARRIER(struct S *p) { func_001F36A8(p); if (p->fe8) RecalcSwOxfFilterForObject__FP2SWP2SO(g_sw, p); }
