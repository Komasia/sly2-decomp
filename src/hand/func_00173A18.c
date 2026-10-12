typedef int qword __attribute__((mode(TI)));
struct G { int a; };
extern struct G D_003DD490;
struct H { char pad[0x90]; qword q90; };
extern struct H D_002DDF40;
void *func_001C4840(struct G *g);
qword func_001A62E8(void *p);
qword func_00173A18(void) { struct G *g = &D_003DD490; if (func_001C4840(g)) return func_001A62E8(func_001C4840(g)); return D_002DDF40.q90; }
