struct S { char pad[0x10]; struct S *x10; };
int func_00132B10(struct S *p, int n);
struct S *func_001A5BF0(struct S *p) { if (func_00132B10(p, 0x30)) return p; return p->x10; }
