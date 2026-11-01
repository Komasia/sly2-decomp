extern int D_002E1E00;
struct G;
extern struct G g_sw;
int IsSwHandsOff__FP2SW(struct G *p);
int func_001C3E90(void) { /*B*/if ((D_002E1E00 & 1) || IsSwHandsOff__FP2SW(&g_sw)) return 1; return 0;/*E*/ }
