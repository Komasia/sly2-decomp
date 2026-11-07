typedef int qword __attribute__((mode(TI)));
struct G { int a; };
extern struct G g_sw;
struct H { char pad[0x90]; qword q90; };
extern struct H g_cm;
void *PloPlayerPo__FP2SW(struct G *g);
qword PosOfLo__FP2LO(void *p);
// name: SafeHouse port (PosCenter)
qword PosCenter__Fv(void) { struct G *g = &g_sw; if (PloPlayerPo__FP2SW(g)) return PosOfLo__FP2LO(PloPlayerPo__FP2SW(g)); return g_cm.q90; }
