struct F { int a[0x1C]; };
void Enter__5AIJOB(void *p);
void func_002333B4(void *p, int c, int n);
void React__8JOBREACTP5AIMSG(void *p, struct F *pf);
// name: SafeHouse port (JOBREACT::Enter)
void Enter__8JOBREACT(void *p) { struct F f; Enter__5AIJOB(p); func_002333B4(&f, 0, sizeof(f)); f.a[0] = 0; React__8JOBREACTP5AIMSG(p, &f); }
